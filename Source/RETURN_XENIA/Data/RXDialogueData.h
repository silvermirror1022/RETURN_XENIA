// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "RXDialogueData.generated.h"

/**
 * 
 */
USTRUCT()
struct FRXDiaglogueData
{
	GENERATED_BODY()

public:

	// NPC 이름 
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DialogueCharTypeTag = FGameplayTag::EmptyTag;

	// 출력할 대화 텍스트
	UPROPERTY(EditDefaultsOnly)
	TArray<FName> DialogueText;

	// 플레이할 2D 사운드
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> DialogueSound;
};

UCLASS()
class RETURN_XENIA_API URXDialogueData : public UDataAsset
{
	GENERATED_BODY()

public:
	const FRXDiaglogueData* FindDialogueCharTypeByTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly)
	TArray<FRXDiaglogueData> DialogueData;
};
