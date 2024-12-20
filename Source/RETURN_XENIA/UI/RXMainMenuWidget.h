﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXMainMenuWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	URXMainMenuWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UImage> ItemInfoImage; //아이템정보에서 참조할 이미지
};
