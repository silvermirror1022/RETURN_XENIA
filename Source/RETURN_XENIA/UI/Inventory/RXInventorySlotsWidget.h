// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXInventorySlotsWidget.generated.h"

class UUniformGridPanel;
class URXInventorySlotWidget;
class URXMainMenuWidget;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXInventorySlotsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXInventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Item;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<TSubclassOf<URXInventorySlotWidget>> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TSubclassOf<UUserWidget> EmptySlotClass;

private:
	UPROPERTY()
	TObjectPtr<URXMainMenuWidget> MainMenuWidget;
};
