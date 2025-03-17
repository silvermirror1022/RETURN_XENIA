// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RXMapData.generated.h"

USTRUCT()
struct FRXMapDataInfo
{
	GENERATED_BODY()

public:
	// ���� �ĺ� �±�
	UPROPERTY(EditDefaultsOnly)
	FName MapName;

	// ���� �� ���
	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath MapAssetPath;
};

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXMapData : public UDataAsset
{
	GENERATED_BODY()

public:
	const FRXMapDataInfo* FindMapDataByName(const FName& InputMapName) const;

	UPROPERTY(EditDefaultsOnly)
	TArray<FRXMapDataInfo> MapData;
};
