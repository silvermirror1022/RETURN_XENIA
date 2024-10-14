// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RXCharacterBase.h"

// Sets default values
ARXCharacterBase::ARXCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARXCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARXCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARXCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

