// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/RXHarpyAnimInstance.h"

URXHarpyAnimInstance::URXHarpyAnimInstance()
	: bIsMove(false), bIsDetected(false), bIsAttack(false), bIsIdle(true)
{
}

void URXHarpyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}

}

void URXHarpyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed == 0 ? 1 : 0;
	}
}
