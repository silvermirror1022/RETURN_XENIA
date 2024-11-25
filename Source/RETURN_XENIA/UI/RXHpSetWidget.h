// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXHpSetWidget.generated.h"

class URXPlayerStatComponent;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXHpSetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	URXHpSetWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:

	void UpdateHpAndShield(int32 InCurrentHp,int32 InCurrentShield);

protected:

	UPROPERTY()
	int32 CurrentHpCnt;

	UPROPERTY()
	int32 CurrentShieldCnt;

	UPROPERTY()
	TObjectPtr<URXPlayerStatComponent> PlayerStatComp;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HpImage")
	TSubclassOf<UUserWidget> HpWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldImage")
	TSubclassOf<UUserWidget> ShieldWidgetClass;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UHorizontalBox> HorizontalBox;
};
