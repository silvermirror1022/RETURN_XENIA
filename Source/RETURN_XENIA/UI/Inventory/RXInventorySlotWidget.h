// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXInventorySlotWidget.generated.h"

class UTexture2D;
class URXMainMenuWidget;
class UButton;
class UImage;
/**
 * 
 */

 // ������ ���õǾ����� �˸��� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventorySlotSelected, URXInventorySlotWidget*, SelectedSlot);

UCLASS()
class RETURN_XENIA_API URXInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXInventorySlotWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// ������ ���õǾ��� �� ����ϴ� ��������Ʈ (�θ� ����)
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotSelected OnSlotSelected;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void ReplaceParentImageWithOwn();

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UButton> Button; 

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<UImage> PressedImage;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "ItemSlotSetting")
	TObjectPtr<UTexture2D> OwnImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlotSetting")
	TObjectPtr<UTexture2D> OwnDescKRImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlotSetting")
	TObjectPtr<UTexture2D> OwnDescENImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSlotSetting")
	FName ItemType;

public:
	UFUNCTION(BlueprintCallable)
	void SetMainMenuWidget(URXMainMenuWidget* InMainMenuWidget);

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class USizeBox> SizeBox;
private:
	UPROPERTY()
	TObjectPtr<URXMainMenuWidget> MainMenuWidget;

	// Ÿ�Կ� ���� ���� �̹��� ���ü� ������ ó���ϴ� ���� �Լ� 
	void UpdateDescriptionImages(bool bIsKorean);
};
