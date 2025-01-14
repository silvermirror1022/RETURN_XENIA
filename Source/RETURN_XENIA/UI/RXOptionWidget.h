// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXOptionWidget.generated.h"

/**
 * 
 */

UCLASS()
class RETURN_XENIA_API URXOptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	URXOptionWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	

};
