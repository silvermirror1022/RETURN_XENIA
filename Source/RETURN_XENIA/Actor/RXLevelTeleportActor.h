﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "RXLevelTeleportActor.generated.h"

UCLASS()
class RETURN_XENIA_API ARXLevelTeleportActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ARXLevelTeleportActor();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

	// 카테고리 TeleportSettings 검색 후 블루프린트 에디터에서 설정해줘야함.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TeleportSettings")
	FGameplayTag DestinationTag; //이동하려는 목적지 태그

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportSettings")
	FName NextLevelName;  // 다른레벨로의 이동

	UFUNCTION(BlueprintNativeEvent)
	void TeleportToOtherLevel();
	virtual void TeleportToOtherLevel_Implementation(); //다른 레벨 여는 함수

	void LoadLevelUsingMapData(); //맵 데이터 접근하는 함수
	void OnLevelLoadCompleted(FSoftObjectPath LoadedMapPath) const; // 로드가 다되고 호출할 함수
	void DelayedOpenLevel(FSoftObjectPath LoadedMapPath) const; // 1.5지연후 호출함수
	
};
