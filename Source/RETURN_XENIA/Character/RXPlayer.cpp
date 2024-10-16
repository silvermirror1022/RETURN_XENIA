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

ARXPlayer::ARXPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
}

void ARXPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
	{

		//Add Input Mapping Context
		if (APlayerController* LocalPlayerController = Cast<APlayerController>(Controller))  // 변경
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
	if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
	{
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
void ARXPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void ARXPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

