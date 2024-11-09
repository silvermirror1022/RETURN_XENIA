// Fill out your copyright notice in the Description page of Project Settings.


#include "System/RXGameInstance.h"
#include "RXGameplayTags.h"
#include "RXDebugHelper.h"
#include "RXAssetManager.h"

URXGameInstance::URXGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentDestinationTag = RXGameplayTags::Teleport_1stFloor_MainMap_Start;
	D(FString::Printf(TEXT("CurrentDestinationTag initialized to: %s"), *CurrentDestinationTag.ToString()));
}

void URXGameInstance::Init()
{
	Super::Init();

	URXAssetManager::Initialize(); //Initialize AssetManager
}

void URXGameInstance::Shutdown()
{
	Super::Shutdown();

}