// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXNewItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXNewItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	URXNewItemWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CloseWidget();
	void CloseWidget_Implementation();
};
