// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	//FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float CurrentHp;

	UPROPERTY()
	float MaxHp;
};
