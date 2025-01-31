﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXPuzzelBase.generated.h"

UCLASS()
class RETURN_XENIA_API ARXPuzzelBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ARXPuzzelBase();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PuzzelEventStart();
	virtual void PuzzelEventStart_Implementation();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void PuzzelEventFinish();
	virtual void PuzzelEventFinish_Implementation();

public:
	// 퍼즐 이름 반환 함수 => 검색용
	UFUNCTION(BlueprintCallable)
	FName GetPuzzelName() const { return PuzzelName; }

protected:
	// 퍼즐의 고유 이름
	UPROPERTY(EditDefaultsOnly, Category = "Puzzel")
	FName PuzzelName;
};
