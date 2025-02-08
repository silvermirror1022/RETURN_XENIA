// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXInventorySlotWidget.generated.h"

class UTexture2D;
class URXMainMenuWidget;
class UButton;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXInventorySlotWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void ReplaceParentImageWithOwn();

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UButton> Button; 

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "OwnChangedImage")
	TObjectPtr<UTexture2D> OwnImage;

public:
	UFUNCTION(BlueprintCallable)
	void SetMainMenuWidget(URXMainMenuWidget* InMainMenuWidget);

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class USizeBox> SizeBox;
private:
	UPROPERTY()
	TObjectPtr<URXMainMenuWidget> MainMenuWidget;

	
};
