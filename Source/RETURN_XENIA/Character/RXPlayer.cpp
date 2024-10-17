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
#include "UI/RXHUDWidget.h"
#include "Player/RXPlayerStatComponent.h"
#include "RXDebugHelper.h"

ARXPlayer::ARXPlayer()
{
	//Camera Spring CDO
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	//Camera CDO
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

		//Add Input Mapping Context
		if (APlayerController* LocalPlayerController = Cast<APlayerController>(Controller))  
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayerController->GetLocalPlayer()))  // 변경
			{
				Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
			}
		}
	}

	D(FString::Printf(TEXT("Current Health: %f, Max Health: %f"), Stat->GetCurrentHp(), Stat->GetMaxHp()));
}

void ARXPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
	{
		//에셋메니저로부터 인풋데이터를 가져와서 각각 액션에 바인딩
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto JumpAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Jump);
		auto MoveAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Move);
		auto LookAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARXPlayer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARXPlayer::Look);

	}
}
void ARXPlayer::SetupHUDWidget(URXHUDWidget* InHUDWidget) 
{
	//Interface Implementation func -> 플레이어 HUD 생성 인터페이스
	if (InHUDWidget)
	{
		InHUDWidget->UpdateHpBar(Stat->GetCurrentHp());

		//RXHUDWidget의 UpdateHpBar를 Stat->OnPlayerHpChanged 델리게이트에 등록
		Stat->OnPlayerHpChanged.AddUObject(InHUDWidget, &URXHUDWidget::UpdateHpBar);
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
}

void ARXPlayer::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.0f);
}
