// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RXPlayer.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "RXGameplayTags.h"
#include "Player/RXPlayerController.h"
#include "System/RXAssetManager.h"
#include "Data/RXInputData.h"
#include "Actor/RXLevelTeleportActor.h"
#include "UI/RXHUDWidget.h"
#include "Character/RXNonPlayer.h"
#include "Player/RXPlayerStatComponent.h"
#include "RXDebugHelper.h"
#include "Actor/RXPuzzelBase.h"
#include "Component/RXPuzzelSpawnManageComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/RXHpSetWidget.h"
#include "System/RXGameInstance.h"
#include "Animation/AnimInstance.h" 
#include "Actor/RXCircularPuzzelBase.h"
#include "Actor/RXKnotHanger.h"

ARXPlayer::ARXPlayer()
{
	// Camera Spring CDO
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	// Camera CDO
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

	// Stat Component CDO
	Stat = CreateDefaultSubobject<URXPlayerStatComponent>(TEXT("PlayerStat"));

	PrimaryActorTick.bCanEverTick = true; // 플레이어 액터 틱 활성화

	bIsCircularPuzzelMode = false;
}

void ARXPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 게임인스턴스 초기화 저장
	GI = Cast<URXGameInstance>(GetWorld()->GetGameInstance());

	// 플레이어 컨트롤러 초기화
	PlayerController = Cast<ARXPlayerController>(GetController());

	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
	{
		// Add Input Mapping Context
		if (APlayerController* LocalPlayerController = Cast<APlayerController>(Controller))  
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayerController->GetLocalPlayer()))  // 변경
			{
				Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
			}
		}
	}
}

void ARXPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
	{
		// 에셋메니저로부터 인풋데이터를 가져와서 각각 액션에 바인딩
		//UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto JumpAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Jump);
		auto MoveAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Move);
		auto LookAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Look);
		auto SprintAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Sprint);
		auto CrouchAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Crouch);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARXPlayer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARXPlayer::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ARXPlayer::StartSprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ARXPlayer::StopSprinting);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ARXPlayer::ToggleCrouch);

		// 인터렉션 섹션 바인딩
		auto InteractAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Interact); // E 키
		auto ProceedDialogueAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_EnterKey); // Enter 키

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ARXPlayer::Interact_IA_EKey);
		EnhancedInputComponent->BindAction(ProceedDialogueAction, ETriggerEvent::Started, this, &ARXPlayer::Interact_IA_EnterKey);	
	}

	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData_Puzzel"))
	{
		auto PuzzelMoveAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_PuzzelMove);
		auto PuzzelResetAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_PuzzelReset);
		auto PuzzelTabAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_PuzzelTab);
		EnhancedInputComponent->BindAction(PuzzelMoveAction, ETriggerEvent::Triggered, this, &ARXPlayer::PuzzelMove);
		EnhancedInputComponent->BindAction(PuzzelResetAction, ETriggerEvent::Started, this, &ARXPlayer::PuzzelReset);
		EnhancedInputComponent->BindAction(PuzzelTabAction, ETriggerEvent::Started, this, &ARXPlayer::PuzzelTab);
	}

	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData_CircularPuzzel"))
	{
		auto CP_ClockWiseRotateKeyAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_CP_ClockWiseRotate);
		auto CP_CounterClockWiseRotateAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_CP_CounterClockWiseRotate);
		auto CP_SwitchTabAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_CP_SwitchTab);
		auto CP_ExitAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_CP_Exit);

		EnhancedInputComponent->BindAction(CP_ClockWiseRotateKeyAction, ETriggerEvent::Started, this, &ARXPlayer::RotateCP_ClockWise);
		EnhancedInputComponent->BindAction(CP_CounterClockWiseRotateAction, ETriggerEvent::Started, this, &ARXPlayer::RotateCP_CounterClockWise);
		EnhancedInputComponent->BindAction(CP_SwitchTabAction, ETriggerEvent::Started, this, &ARXPlayer::ChangeSelectedWheel);
		EnhancedInputComponent->BindAction(CP_ExitAction, ETriggerEvent::Started, this, &ARXPlayer::ExitCircularPuzzel);
		
	}

	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData_KnotHang"))
	{
		auto QKey_HangKnotAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_KnotHang_Hang);
		auto BKey_ExitHangingKnotAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_KnotHang_Exit);

		EnhancedInputComponent->BindAction(QKey_HangKnotAction, ETriggerEvent::Started, this, &ARXPlayer::HangKnotChar);
		EnhancedInputComponent->BindAction(BKey_ExitHangingKnotAction, ETriggerEvent::Started, this, &ARXPlayer::ExitHangingKnot);
	}
	
	/*게임 UI 관련 액션 바인딩은 플레이어컨트롤러에서 개별 분리*/
}

void ARXPlayer::SetupHUDWidget(URXHUDWidget* InHUDWidget)
{
	// Interface Implementation func -> 플레이어 HUD 생성 인터페이스
	if (InHUDWidget)
	{
		if (GI = Cast<URXGameInstance>(GetWorld()->GetGameInstance()))
		{
			InHUDWidget->UpdateHpSet(GI->GetGI_Hp(), GI->GetGI_Shield());
			InHUDWidget->UpdateShieldCoolTime(GI->IsProfileStatusAcquired("Kaira_necklace"));
		}

		// 델리게이트 연결
		Stat->OnPlayerHpAndShieldChanged.AddUObject(InHUDWidget->HpSet, &URXHpSetWidget::UpdateHpAndShield);

		// Player의 체력이 0이 됬을 때 플레이어 죽음 함수 구독
		Stat->OnPlayerHpZero.AddUObject(this, &ARXPlayer::SetDead);
	}
}
void ARXPlayer::UpdateDetectedActor()
{
	FHitResult Hit;
	FVector Start = GetCapsuleComponent()->GetComponentLocation();  // 캐릭터 캡슐 위치
	FVector End = Start + (GetActorForwardVector()* 80.0f);  // 카메라 방향으로 80만큼

	float SphereRadius = 45.f;  // 스피어의 반지름 (기본값: 45)
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);  // 자신의 캐릭터는 무시
	Params.bReturnPhysicalMaterial = false;

	// 디버그용으로 스피어 범위를 시각화 (DrawDebugSphere)
	if (GetWorld())
	{
		// Start 위치에서 End까지의 방향으로 스피어를 그려서 디버깅 가능
		DrawDebugSphere(GetWorld(), End, SphereRadius, 12, FColor::Green, false, 0.5f, 0, 1.0f);
	}

	// 트레이스 시 'Pawn' 채널을 사용하여 NPC를 감지
    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn); // NPC 감지용 채널 설정
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); // 텔레포트 엑터 감지용 채널 설정

	// 스피어 트레이스를 실행하여 NPC 또는 텔레포트엑터를 감지
	if (GetWorld()->SweepSingleByObjectType(Hit, Start, End, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(SphereRadius), Params))
	{
		if (ARXNonPlayer* NPC = Cast<ARXNonPlayer>(Hit.GetActor()))
		{
			DetectedNPC = NPC;  // 감지된 NPC로 업데이트
		}
		else if(ARXLevelTeleportActor* TPActor = Cast<ARXLevelTeleportActor>(Hit.GetActor()))
		{
			DetectedTeleportActor = TPActor; // 감지된 텔레포트엑터 업데이트
		}
		else if(ARXPuzzelBase* PuzzelActor = Cast<ARXPuzzelBase>(Hit.GetActor()))
		{
			DetectedPuzzelActor = PuzzelActor;
		}
		else if (ARXKnotHanger* KnotHangerActor = Cast<ARXKnotHanger>(Hit.GetActor()))
		{
			DetectedKnotHangerActor = KnotHangerActor;
		}
		else
		{
			ResetDetectedActors();
		}
	}
	else
	{
		ResetDetectedActors();
	}
}
void ARXPlayer::ResetDetectedActors()
{
	DetectedNPC = nullptr;
	DetectedTeleportActor = nullptr;
	DetectedPuzzelActor = nullptr;
	DetectedCircularPuzzelActor = nullptr;
	DetectedKnotHangerActor = nullptr;
}
void ARXPlayer::Interact_IA_EKey()
{
	if (DetectedNPC)  // 대화중이라면 빠저나가기
	{   //if (DetectedNPC && DetectedNPC->bIsTalking) 
		return;
	}

	UpdateDetectedActor();

	if (DetectedNPC && !DetectedNPC->bIsTalking)  // 각각 유효한지 확인
	{
		DetectedNPC->StartDialogue();
	}
	else if (DetectedTeleportActor)
	{
		DetectedTeleportActor->TeleportToOtherLevel();
	}
	else if(DetectedKnotHangerActor)
	{
		DetectedKnotHangerActor->ChangeToCamView();
	}
	else if (DetectedPuzzelActor)
	{
		// 퍼즐이 CircularPuzzel인지 확인
		if (DetectedCircularPuzzelActor = Cast<ARXCircularPuzzelBase>(DetectedPuzzelActor))
		{
			// CircularPuzzelBase의 PuzzelEventStart 호출
			if (!GI->IsPuzzelStatusAcquired(DetectedCircularPuzzelActor->GetPuzzelName().ToString()))
			{
				DetectedCircularPuzzelActor = Cast<ARXCircularPuzzelBase>(DetectedCircularPuzzelActor);
				DetectedCircularPuzzelActor->PuzzelEventStart();
			}
		}
		else
		{
			// 일반 PuzzelBase의 PuzzelEventStart 호출
			if (!GI->IsPuzzelStatusAcquired(DetectedPuzzelActor->GetPuzzelName().ToString()))
			{
				DetectedPuzzelActor->PuzzelEventStart();
			}
		}
	}
}

void ARXPlayer::Interact_IA_EnterKey()
{
	
	if (DetectedNPC && DetectedNPC->bIsTalking)
	{
		DetectedNPC->DisplayDialogue();  // 대화 진행 메서드
	}
}

void ARXPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void ARXPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * GI->GetMouseSensitivityValue()* 0.3f);

		// 마우스 비반전 컨트롤 마우스를 위로 움직이면 위를 보게
		AddControllerPitchInput(-LookAxisVector.Y * GI->GetMouseSensitivityValue() * 0.1f);
	}

}
void ARXPlayer::StartSprinting()
{
	// 스프린트 시작(Left Shift o)
	if(GI->IsProfileStatusAcquired("RedCloak"))
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 650.0f;
	}
	
}

void ARXPlayer::StopSprinting()
{
	// 스프린트 해제(Left Shift x)
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}


void ARXPlayer::ToggleCrouch()
{
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	if (!MovementComp) return;

	// 땅에 있을 때만 앉을 수 있도록 체크
	if (MovementComp->IsMovingOnGround())
	{
		if (MovementComp->IsCrouching())
		{
			UnCrouch();
		}
		else
		{
			Crouch();
		}
	}
}

void ARXPlayer::MoveToTagLocation(FName TagName, float ZOffSet)
{	// 퍼즐 포지션 이동함수 => 퍼즐이벤트 컴포넌트에서 사용됨.

	// 태그로 지정된 액터 검색
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagName, TaggedActors);

	if (TaggedActors.Num() > 0)
	{
		// 첫 번째 태그 액터의 위치로 이동
		AActor* TargetActor = TaggedActors[0];
		if (TargetActor)
		{
			FVector TargetLocation = TargetActor->GetActorLocation();
			TargetLocation.Z += ZOffSet; // Z축 오프셋 추가
			SetActorLocation(TargetLocation);

			// 타겟 액터의 회전을 가져와 플레이어에 적용
			FRotator TargetRotation = TargetActor->GetActorRotation();
			SetActorRotation(TargetRotation);
		}
	}
}

void ARXPlayer::PuzzelMove(const FInputActionValue& Value)
{
	// 퍼즐 모드시 이동 로직
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 대각선 입력 감지
		if (MovementVector.X != 0.0f && MovementVector.Y != 0.0f)
		{
			// 대각선 입력 시 이동하지 않음
			return;
		}

		// 퍼즐 모드에서는 월드 좌표계를 기반으로 이동
		if (MovementVector.X != 0.0f)
		{
			FVector ForwardDirection = FVector::ForwardVector;
			AddMovementInput(ForwardDirection, MovementVector.X);
		}

		if (MovementVector.Y != 0.0f)
		{
			FVector RightDirection = FVector::RightVector;
			AddMovementInput(RightDirection, MovementVector.Y);
		}
	}
}

void ARXPlayer::PuzzelReset()
{
	// 퍼즐베이스엑터를 가져와서 가지고 있는 스폰매니저 컴포넌트에 접근해서 함수 호출
	TArray<AActor*> PuzzelActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARXPuzzelBase::StaticClass(), PuzzelActors);

	for (AActor* Actor : PuzzelActors)
	{
		if (ARXPuzzelBase* PuzzelBase = Cast<ARXPuzzelBase>(Actor))
		{
			URXPuzzelSpawnManageComponent* PSMC = PuzzelBase->FindComponentByClass<URXPuzzelSpawnManageComponent>();

			if (PSMC)
			{
				PSMC->ResetCurrentLevel();
			}
		}
	}
}

void ARXPlayer::PuzzelTab()
{
	// 블라인드 퍼즐에서만 사용하는 함수 (힌트를 일정시간에 보이게함)
	// 퍼즐베이스엑터를 가져와서 가지고 있는 스폰매니저 컴포넌트에 접근해서 함수 호출
	TArray<AActor*> PuzzelActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARXPuzzelBase::StaticClass(), PuzzelActors);

	for (AActor* Actor : PuzzelActors)
	{
		if (ARXPuzzelBase* PuzzelBase = Cast<ARXPuzzelBase>(Actor))
		{
			URXPuzzelSpawnManageComponent* PSMC = PuzzelBase->FindComponentByClass<URXPuzzelSpawnManageComponent>();

			if (PSMC)
			{
				PSMC->VisibleHintTile();
			}
		}
	}
}

void ARXPlayer::ExitCircularPuzzel()
{
	if (!bIsCircularPuzzelMode) return;
	DetectedCircularPuzzelActor->PuzzelEventFinish();
}

void ARXPlayer::RotateCP_CounterClockWise()
{
	if (!bIsCircularPuzzelMode) return;
	DetectedCircularPuzzelActor->RotateToCounterClockWise();
}

void ARXPlayer::RotateCP_ClockWise() 
{
	if (!bIsCircularPuzzelMode) return;
	DetectedCircularPuzzelActor->RotateToClockWise();
}

void ARXPlayer::ChangeSelectedWheel()
{
	if (!bIsCircularPuzzelMode) return;
	DetectedCircularPuzzelActor->SwitchSelectedWheel();
}

void ARXPlayer::HangKnotChar()
{
	if(DetectedKnotHangerActor->isCamView)
	{
		DetectedKnotHangerActor->HangKnotAction();
	}
}

void ARXPlayer::ExitHangingKnot() 
{
	DetectedKnotHangerActor->ReturnToPlayerView();
}

void ARXPlayer::SetDead()
{
	// 플레이어 사망 함수
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);

	// DisableInput(PlayerController); //입력 멈추기
	GetCharacterMovement()->DisableMovement();  // 이동 비활성화
	PlayerController->SetIgnoreMoveInput(true);

	// 일정 시간 후에 리스폰하도록 타이머 설정 (3초 후)
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ARXPlayer::DeadRespawn, 3.0f, false);

}
void ARXPlayer::DeadRespawn()
{
	if (PlayerController)
	{
		// 플레이어 컨트롤러에서 리스폰 로직 호출
		PlayerController->RespawnPlayerAtCheckPoint();

		// 리스폰 후 플레이어 Pawn의 입력 및 충돌 등을 복구하는 로직 추가
		SetActorEnableCollision(true);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		PlayerController->SetIgnoreMoveInput(false);

		// 애니메이션 상태 초기화 
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			// 애니메이션 몽타주나 상태를 재시작할 필요 없이 상태 머신에서 IDLE로 돌아가도록 처리
			AnimInstance->Montage_Stop(0.2f);  // 현재 애니메이션을 빠르게 종료시키기
			//AnimInstance->SetPlayRate(1.0f);   // 애니메이션 속도 복구
		}
	}
}
void ARXPlayer::PlayDeadAnimation()
{
	// 추가 페이드 로직 블루프린트에서 확장 처리
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	IsBossStage ? AnimInstance->Montage_Play(DeadMontageInBossMap, 1.0f) : AnimInstance->Montage_Play(DeadMontage, 1.0f);
	//AnimInstance->Montage_Play(DeadMontage, 1.0f);
}
