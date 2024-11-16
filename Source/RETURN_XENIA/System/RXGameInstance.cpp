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

// For Memory Dynamic Control Section
bool URXGameInstance::SetMemoryStatusAcquired(FString StatusName)
{
	for (FStatus& Status : MemoryStatusArray)
	{
		if (Status.Name == StatusName)
		{
			Status.bIsAcquired = true;
			return true; 
		}
	}
	return false; 
}
bool URXGameInstance::IsMemoryStatusAcquired(FString StatusName) const
{
	for (const FStatus& Status : MemoryStatusArray)
	{
		if (Status.Name == StatusName)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Status Name: %s, Acquired: %s"), *Status.Name, Status.bIsAcquired ? TEXT("True") : TEXT("False"));
			return Status.bIsAcquired;
		}
	}
	return false;
}

// For Profile Dynamic Control Section
bool URXGameInstance::SetProfileStatusAcquired(FString StatusName)
{
	for (FStatus& Status : ProfileStatusArray)
	{
		if (Status.Name == StatusName)
		{
			Status.bIsAcquired = true;
			return true; 
		}
	}
	return false; 
}
bool URXGameInstance::IsProfileStatusAcquired(FString StatusName) const
{
	for (const FStatus& Status : ProfileStatusArray)
	{
		if (Status.Name == StatusName)
		{
			return Status.bIsAcquired; 
		}
	}
	return false; 
}

// For Item Dynamic Control Function Section
bool URXGameInstance::SetItemStatusAcquired(FString StatusName)
{	
	for (FStatus& Status : ItemStatusArray)
	{
		if (Status.Name == StatusName)
		{
			Status.bIsAcquired = true;
			return true;
		}
	}
	return false;
}
bool URXGameInstance::IsItemStatusAcquired(FString StatusName) const
{
	for (const FStatus& Status : ItemStatusArray)
	{
		if (Status.Name == StatusName)
		{
			return Status.bIsAcquired;
		}
	}
	return false;
}