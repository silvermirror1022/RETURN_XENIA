// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXPapyrusSlotsWidget.generated.h"

/**
 * 
 */
class UUniformGridPanel;
class URXInventorySlotWidget;
class URXMainMenuWidget;

UCLASS()
class RETURN_XENIA_API URXPapyrusSlotsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	URXPapyrusSlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

	// 파피루스 슬롯들을 배치할 GridPanel
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Item;

public:
	// 파피루스 아이템에 사용할 슬롯 위젯 클래스 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<TSubclassOf<URXInventorySlotWidget>> ItemClass;

	// 빈 슬롯에 사용할 위젯 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TSubclassOf<UUserWidget> EmptySlotClass;

	// 선택 해제 함수
	void ClearSelection();
private:
	// 부모 MainMenuWidget (예: 오른쪽에 아이템 설명 등을 표시)
	UPROPERTY()
	TObjectPtr<URXMainMenuWidget> MainMenuWidget;

	// 슬롯 선택 델리게이트 핸들러
	UFUNCTION()
	void HandleSlotSelected(URXInventorySlotWidget* SelectedSlot);
};
