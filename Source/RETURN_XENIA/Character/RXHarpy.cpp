// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/RXHarpy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARXHarpy::ARXHarpy()
{
	GetCapsuleComponent()->InitCapsuleSize(100.f, 100.f);
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -100.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, 1000.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

// Called when the game starts or when spawned
void ARXHarpy::BeginPlay()
{
	Super::BeginPlay();
	
}



