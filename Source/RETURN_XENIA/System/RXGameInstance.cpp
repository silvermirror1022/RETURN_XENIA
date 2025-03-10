// Fill out your copyright notice in the Description page of Project Settings.


#include "System/RXGameInstance.h"
#include "RXGameplayTags.h"
#include "RXDebugHelper.h"
#include "RXAssetManager.h"
#include "RXSaveGame.h"

URXGameInstance::URXGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentDestinationTag = RXGameplayTags::Teleport_1stFloor_MainMap_Start;
	//D(FString::Printf(TEXT("CurrentDestinationTag initialized to: %s"), *CurrentDestinationTag.ToString()));

	CurrentLevelName = "NoahHouse";
	SetGI_Hp(3);
	SetGI_Shield(1);

	ObservedMapStatus = 1;
	AcquiredPapyrusNum = 0;
	bIsKorean = true;
	bIsNoahGetup = false;
	bIsAfterDisaster = false;
	bIsAntuqDialogueEventFinished = false; 
	bIsAmarkaDialogueEventFinished = false; 
	bIsWinikDialogueEventFinished = false;
	bIsAmarkaDialogueItemEventFinished = false;
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

// For PuzzelEvent Start Interaction Dynamic Control Function Section
bool URXGameInstance::SetPuzzelStatusAcquired(FString StatusName)
{
	for (FStatus& Status : PuzzelClearStatusArray)
	{
		if (Status.Name == StatusName)
		{
			Status.bIsAcquired = true;
			return true;
		}
	}
	return false;
}

bool URXGameInstance::IsPuzzelStatusAcquired(FString StatusName) const
{
	for (const FStatus& Status : PuzzelClearStatusArray)
	{
		if (Status.Name == StatusName)
		{
			return Status.bIsAcquired;
		}
	}
	return false;
}
// For ObservedMap User Experience Dynamic Control Function Section
void URXGameInstance::SetObservedMapStatus(int32 Level)
{
	ObservedMapStatus = Level;
}

int URXGameInstance::ReturnObservedMapStatus() 
{
	return ObservedMapStatus;
}

void URXGameInstance::InitializeAllVariable()
{
	CurrentDestinationTag = RXGameplayTags::Teleport_1stFloor_MainMap_Start;
	CurrentLevelName = "NoahHouse";
	SetGI_Hp(3);
	SetGI_Shield(1);
	ObservedMapStatus = 1;
	AcquiredPapyrusNum = 0;
	bIsKorean = true;
	bIsNoahGetup = false;
	bIsAfterDisaster = false;
	bIsAntuqDialogueEventFinished = false;
	bIsAmarkaDialogueEventFinished = false;
	bIsWinikDialogueEventFinished = false;
	bIsAmarkaDialogueItemEventFinished = false;

	// MemoryStatusArray: 첫번째 요소만 true, 나머지는 false
	if (MemoryStatusArray.Num() > 0)
	{
		MemoryStatusArray[0].bIsAcquired = true; // 예외: 첫번째만 true로 유지
		for (int32 i = 1; i < MemoryStatusArray.Num(); i++)
		{
			MemoryStatusArray[i].bIsAcquired = false;
		}
	}

	// ProfileStatusArray: 모두 false로 초기화
	for (int32 i = 0; i < ProfileStatusArray.Num(); i++)
	{
		ProfileStatusArray[i].bIsAcquired = false;
	}

	// ItemStatusArray: 모두 false로 초기화
	for (int32 i = 0; i < ItemStatusArray.Num(); i++)
	{
		ItemStatusArray[i].bIsAcquired = false;
	}

	// PuzzelClearStatusArray: 모두 false로 초기화
	for (int32 i = 0; i < PuzzelClearStatusArray.Num(); i++)
	{
		PuzzelClearStatusArray[i].bIsAcquired = false;
	}
}


