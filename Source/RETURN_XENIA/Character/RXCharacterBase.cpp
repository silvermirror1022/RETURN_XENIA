// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RXCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARXCharacterBase::ARXCharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;  // 이동 방향에 맞춰 회전
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);  // 회전 속도
	GetCharacterMovement()->JumpZVelocity = 700.f;  // 점프 속도
	GetCharacterMovement()->AirControl = 0.35f;  // 공중에서의 제어
	GetCharacterMovement()->MaxWalkSpeed = 500.f;  // 최대 걷기 속도
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;  // 최소 걷기 속도
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;  // 걷기 제동 속도

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));


}

