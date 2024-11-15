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
bool URXGameInstance::SetMemoryStatusAcquired(FString StatusName)
{
	for (FStatus& Status : MemoryStatusArray)
	{
		if (Status.Name == StatusName)
		{
			Status.bIsAcquired = true;
			return true; // 성공적으로 값을 변경한 경우
		}
	}
	return false; // 해당 이름의 상태를 찾지 못한 경우
}

bool URXGameInstance::SetProfileStatusAcquired(FString StatusName)
{
	for (FStatus& Status : ProfileStatusArray)
	{
		if (Status.Name == StatusName)
		{
			Status.bIsAcquired = true;
			return true; // 성공적으로 값을 변경한 경우
		}
	}
	return false; // 해당 이름의 상태를 찾지 못한 경우
}
bool URXGameInstance::IsMemoryStatusAcquired(FString StatusName) const
{
	for (const FStatus& Status : MemoryStatusArray)
	{
		if (Status.Name == StatusName)
		{
			UE_LOG(LogTemp, Warning, TEXT("Status Name: %s, Acquired: %s"), *Status.Name, Status.bIsAcquired ? TEXT("True") : TEXT("False"));
			return Status.bIsAcquired; // 해당 상태의 획득 여부를 반환
		}
	}
	return false; // 해당 이름의 상태를 찾지 못한 경우 false 반환
}

bool URXGameInstance::IsProfileStatusAcquired(FString StatusName) const
{
	for (const FStatus& Status : ProfileStatusArray)
	{
		if (Status.Name == StatusName)
		{
			return Status.bIsAcquired; // 해당 상태의 획득 여부를 반환
		}
	}
	return false; // 해당 이름의 상태를 찾지 못한 경우 false 반환
}