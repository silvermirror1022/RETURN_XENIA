// Fill out your copyright notice in the Description page of Project Settings.


#include "System/RXSaveGame.h"
#include "System/RXGameInstance.h"

URXSaveGame::URXSaveGame()
{
	// 기본값 설정
	CheckpointTransform = FTransform::Identity;
	CurrentDestinationTag = FGameplayTag(); // 기본 태그
	CurrentLevelName = "NoahHouse";
	GI_Hp = 0;
	GI_Shield = 0;
	SliderValues = FSliderValues(); // 기본 생성자 호출
	bIsKorean = true;
	bIsAfterDisaster = false;
	bIsKairaDialogueEventFinished = false;
	bIsAntuqDialogueEventFinished = false;
	bIsAmarkaDialogueEventFinished = false;
	bIsAmarkaDialogueItemEventFinished = false;
	bIsWinikDialogueEventFinished = false;
}

void URXSaveGame::CaptureDataFromGameInstance(URXGameInstance* GameInstance)
{
	if (!GameInstance)
	{
		return;
	}

	// 게임 인스턴스의 데이터를 SaveGame 변수에 복사
	CheckpointTransform = GameInstance->CheckpointTransform;
	CurrentDestinationTag = GameInstance->CurrentDestinationTag;
	CurrentLevelName = GameInstance->CurrentLevelName;
	MemoryStatusArray = GameInstance->MemoryStatusArray;
	ProfileStatusArray = GameInstance->ProfileStatusArray;
	ItemStatusArray = GameInstance->ItemStatusArray;
	PuzzelClearStatusArray = GameInstance->PuzzelClearStatusArray;
	GI_Hp = GameInstance->GetGI_Hp();
	GI_Shield = GameInstance->GetGI_Shield();
	SliderValues = GameInstance->SliderValues;
	bIsKorean = GameInstance->bIsKorean;
	bIsAfterDisaster = GameInstance->bIsAfterDisaster;
	bIsKairaDialogueEventFinished = GameInstance->bIsKairaDialogueEventFinished;
	bIsAntuqDialogueEventFinished = GameInstance->bIsAntuqDialogueEventFinished;
	bIsAmarkaDialogueEventFinished = GameInstance->bIsAmarkaDialogueEventFinished;
	bIsAmarkaDialogueItemEventFinished = GameInstance->bIsAmarkaDialogueItemEventFinished;
	bIsWinikDialogueEventFinished = GameInstance->bIsWinikDialogueEventFinished;
}

void URXSaveGame::ApplyDataToGameInstance(URXGameInstance* GameInstance)
{
	if (!GameInstance)
	{
		return;
	}

	// 저장된 데이터를 게임 인스턴스에 적용
	GameInstance->CheckpointTransform = CheckpointTransform;
	GameInstance->CurrentDestinationTag = CurrentDestinationTag;
	GameInstance->CurrentLevelName = CurrentLevelName;
	GameInstance->MemoryStatusArray = MemoryStatusArray;
	GameInstance->ProfileStatusArray = ProfileStatusArray;
	GameInstance->ItemStatusArray = ItemStatusArray;
	GameInstance->PuzzelClearStatusArray = PuzzelClearStatusArray;
	GameInstance->SetGI_Hp(GI_Hp);
	GameInstance->SetGI_Shield(GI_Shield);
	GameInstance->SliderValues = SliderValues;
	GameInstance->bIsKorean = bIsKorean;
	GameInstance->bIsAfterDisaster = bIsAfterDisaster;
	GameInstance->bIsKairaDialogueEventFinished = bIsKairaDialogueEventFinished;
	GameInstance->bIsAntuqDialogueEventFinished = bIsAntuqDialogueEventFinished;
	GameInstance->bIsAmarkaDialogueEventFinished = bIsAmarkaDialogueEventFinished;
	GameInstance->bIsAmarkaDialogueItemEventFinished = bIsAmarkaDialogueItemEventFinished;
	GameInstance->bIsWinikDialogueEventFinished = bIsWinikDialogueEventFinished;
}
