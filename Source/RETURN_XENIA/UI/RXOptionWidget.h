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
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class USlider> BrightnessSlider; 

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class USlider> MasterVolumeSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class USlider> MusicVolumeSlider;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class USlider> SFXVolumeSlider;

};