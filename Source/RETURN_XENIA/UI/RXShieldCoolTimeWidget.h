// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXShieldCoolTimeWidget.generated.h"

class UTexture2D;
class UImage;
class URXPlayerStatComponent;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXShieldCoolTimeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXShieldCoolTimeWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateCoolTimeImage(int32 ImageIdx);
	void UpdateCoolTimeFullImage();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoolTimeImages")
	TArray<TObjectPtr<UTexture2D>> CoolTimeImages;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> SecondShowImage;

	UPROPERTY()
	TObjectPtr<URXPlayerStatComponent> PlayerStatComp;
};
