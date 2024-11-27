// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	URXHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHpSet(int32, int32);
	void UpdateShieldCoolTime(bool);

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class URXHpSetWidget> HpSet;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class URXShieldCoolTimeWidget> ShieldCoolTime;
};
