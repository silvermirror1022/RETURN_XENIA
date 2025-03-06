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

	// ���Ƿ罺 ���Ե��� ��ġ�� GridPanel
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Item;

public:
	// ���Ƿ罺 �����ۿ� ����� ���� ���� Ŭ���� �迭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<TSubclassOf<URXInventorySlotWidget>> ItemClass;

	// �� ���Կ� ����� ���� Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TSubclassOf<UUserWidget> EmptySlotClass;

	// ���� ���� �Լ�
	void ClearSelection();
private:
	// �θ� MainMenuWidget (��: �����ʿ� ������ ���� ���� ǥ��)
	UPROPERTY()
	TObjectPtr<URXMainMenuWidget> MainMenuWidget;

	// ���� ���� ��������Ʈ �ڵ鷯
	UFUNCTION()
	void HandleSlotSelected(URXInventorySlotWidget* SelectedSlot);
};
