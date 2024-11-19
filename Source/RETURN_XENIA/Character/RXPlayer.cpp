// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RXPlayer.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "RXGameplayTags.h"
#include "Player/RXPlayerController.h"
#include "System/RXAssetManager.h"
#include "Data/RXInputData.h"
#include "Actor/RXLevelTeleportActor.h"
#include "UI/RXHUDWidget.h"
#include "Character/RXNonPlayer.h"
#include "Player/RXPlayerStatComponent.h"
#include "RXDebugHelper.h"

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
}

void ARXPlayer::BeginPlay()
{
	Super::BeginPlay();

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

	//D(FString::Printf(TEXT("Current Health: %f, Max Health: %f"), Stat->GetCurrentHp(), Stat->GetMaxHp()));
}

void ARXPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
	{
		// 에셋메니저로부터 인풋데이터를 가져와서 각각 액션에 바인딩
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto JumpAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Jump);
		auto MoveAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Move);
		auto LookAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARXPlayer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARXPlayer::Look);

		// 인터렉션 섹션 바인딩
		auto InteractAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Interact); // E 키
		auto ProceedDialogueAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_EnterKey); // Enter 키

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ARXPlayer::Interact_IA_EKey);
		EnhancedInputComponent->BindAction(ProceedDialogueAction, ETriggerEvent::Started, this, &ARXPlayer::Interact_IA_EnterKey);

		// ESC Key 게임퍼즈메뉴 바인딩
		//auto ESCGamePauseMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_ESCKey); // ESC(Escape) 키
		//EnhancedInputComponent->BindAction(ESCGamePauseMenuAction, ETriggerEvent::Started, this, &ARXPlayer::GameMenuPause_ESCKey);
	}
}
void ARXPlayer::SetupHUDWidget(URXHUDWidget* InHUDWidget)
{
	// Interface Implementation func -> 플레이어 HUD 생성 인터페이스
	if (InHUDWidget)
	{
		InHUDWidget->UpdateHpBar(Stat->GetCurrentHp());

		// RXHUDWidget의 UpdateHpBar를 Stat->OnPlayerHpChanged 델리게이트에 등록
		Stat->OnPlayerHpChanged.AddUObject(InHUDWidget, &URXHUDWidget::UpdateHpBar);
	}
}
void ARXPlayer::UpdateDetectedActor()
{
	FHitResult Hit;
	FVector Start = GetCapsuleComponent()->GetComponentLocation();  // 캐릭터 캡슐 위치
	FVector End = Start + (GetActorForwardVector()* 80.0f);  // 카메라 방향으로 80만큼

	float SphereRadius = 50.0f;  // 스피어의 반지름 (기본값: 50)
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);  // 자신의 캐릭터는 무시
	Params.bReturnPhysicalMaterial = false;

	// 디버그용으로 스피어 범위를 시각화 (DrawDebugSphere)
	if (GetWorld())
	{
		// Start 위치에서 End까지의 방향으로 스피어를 그려서 디버깅 가능
		DrawDebugSphere(GetWorld(), End, SphereRadius, 12, FColor::Green, false, 1.0f, 0, 1.0f);
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
}
void ARXPlayer::Interact_IA_EKey()
{
	UpdateDetectedActor();

	if (DetectedNPC && !DetectedNPC->bIsTalking)  // DetectedNPC가 유효한지 확인
	{
		DetectedNPC->StartDialogue();
	}
	else if (DetectedTeleportActor)
	{
		DetectedTeleportActor->TeleportToOtherLevel();
	}
}

void ARXPlayer::Interact_IA_EnterKey()
{
	if (DetectedNPC && DetectedNPC->bIsTalking)
	{
		DetectedNPC->DisplayDialogue();  // 대화 진행 메서드
	}
}
float ARXPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;
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
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void ARXPlayer::SetDead()
{
	//플레이어 사망 함수
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);

	//DisableInput(PlayerController); //입력 멈추기
	GetCharacterMovement()->DisableMovement();  // 이동 비활성화
	PlayerController->SetIgnoreMoveInput(true);
}

void ARXPlayer::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.0f);
}
