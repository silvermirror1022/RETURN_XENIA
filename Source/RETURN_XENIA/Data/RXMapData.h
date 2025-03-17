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
	// 맵의 식별 태그
	UPROPERTY(EditDefaultsOnly)
	FName MapName;

	// 실제 맵 경로
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
