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

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DialogueCharTypeTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> DialogueText;
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
