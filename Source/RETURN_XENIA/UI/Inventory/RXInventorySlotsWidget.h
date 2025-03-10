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

	// GridPanel에 추가된 슬롯들을 관리하는 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Item;

public:
	// 슬롯에 사용할 아이템 클래스 배열 (획득된 아이템마다 지정된 슬롯 위젯 클래스)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<TSubclassOf<URXInventorySlotWidget>> ItemClass;

	// 빈 슬롯에 사용할 위젯 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TSubclassOf<UUserWidget> EmptySlotClass;

	// 선택 해제 함수
	void ClearSelection();
private:
	// 부모 MainMenuWidget
	UPROPERTY()
	TObjectPtr<URXMainMenuWidget> MainMenuWidget;

	// 슬롯 선택 델리게이트 핸들러
	UFUNCTION()
	void HandleSlotSelected(URXInventorySlotWidget* SelectedSlot);

};
