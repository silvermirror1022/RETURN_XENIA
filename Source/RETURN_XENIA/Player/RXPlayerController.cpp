// Fill out your copyright notice in the Description page of Project Settings.

#include "System/RXAssetManager.h"
#include "Player/RXPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Data/RXInputData.h"
#include "RXGameplayTags.h"
#include "Character/RXPlayer.h"

ARXPlayerController::ARXPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void ARXPlayerController::BeginPlay()
{
}

void ARXPlayerController::SetupInputComponent()
{
}
