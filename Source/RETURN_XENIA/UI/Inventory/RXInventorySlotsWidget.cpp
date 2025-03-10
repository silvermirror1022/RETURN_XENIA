// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/RXInventorySlotsWidget.h"
#include "System/RXGameInstance.h"
#include "Components/UniformGridPanel.h"
#include "UI/RXMainMenuWidget.h"
#include "UI/Inventory/RXInventorySlotWidget.h"
#include "Components/Image.h"

URXInventorySlotsWidget::URXInventorySlotsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void URXInventorySlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 계층에서 MainMenuWidget 검색
	MainMenuWidget = GetTypedOuter<URXMainMenuWidget>();

	URXGameInstance* GI = GetWorld()->GetGameInstance<URXGameInstance>();
	if (!GI || !GridPanel_Item) return;

	TArray<FString> ItemNames = { TEXT("KnotChar_Tutorial"), TEXT("KnotChar1F_1"), TEXT("KnotChar1F_2"), TEXT("KnotChar1F_3"),
		TEXT("KnotChar2F_1"), TEXT("KnotChar2F_2"),TEXT("KnotChar2F_3"),
		TEXT("HintPaper") };

	constexpr int X_COUNT = 3;
	constexpr int Y_COUNT = 3;
	int32 CurrentItemIndex = 0;

	// 획득된 아이템 리스트만 필터링
	TArray<int32> AcquiredItemIndices;
	for (int32 i = 0; i < ItemNames.Num(); i++)
	{
		if (GI->IsItemStatusAcquired(ItemNames[i]))
		{
			AcquiredItemIndices.Add(i);
		}
	}

	// 슬롯에 아이템 추가
	for (int32 Y = 0; Y < Y_COUNT; Y++)
	{
		for (int32 X = 0; X < X_COUNT; X++)
		{
			// 현재 획득된 아이템의 인덱스가 범위를 초과하면 빈 슬롯 추가
			if (CurrentItemIndex >= AcquiredItemIndices.Num())
			{
				if (EmptySlotClass)
				{
					UUserWidget* SlotWidget = CreateWidget<UUserWidget>(GetOwningPlayer(), EmptySlotClass);
					GridPanel_Item->AddChildToUniformGrid(SlotWidget, Y, X);
				}
			}
			else
			{
				// 획득된 아이템 추가
				int32 ItemIndex = AcquiredItemIndices[CurrentItemIndex];
				if (ItemIndex < ItemClass.Num())
				{
					URXInventorySlotWidget* SlotWidget = CreateWidget<URXInventorySlotWidget>(GetOwningPlayer(), ItemClass[ItemIndex]);
					SlotWidget->SetMainMenuWidget(MainMenuWidget);

					GridPanel_Item->AddChildToUniformGrid(SlotWidget, Y, X);

					// 각 슬롯 위젯의 델리게이트에 자신의 핸들러를 바인딩
					SlotWidget->OnSlotSelected.AddDynamic(this, &URXInventorySlotsWidget::HandleSlotSelected);

					CurrentItemIndex++; // 아이템 추가 시 인덱스 증가
				}
			}
		}
	}

	// 만약 GridPanel에 슬롯이 존재하고, 첫 슬롯에 아이템이 있다면
	if (GridPanel_Item->GetChildrenCount() > 0)
	{
		URXInventorySlotWidget* FirstSlot = Cast<URXInventorySlotWidget>(GridPanel_Item->GetChildAt(0));
		if (FirstSlot && FirstSlot->OwnImage) // 아이템이 존재하면
		{
			// 첫 번째 슬롯을 강제로 pressed 상태로 만듦 (이미지 업데이트 및 PressedImage Visible)
			FirstSlot->ReplaceParentImageWithOwn();
		}
	}
}

void URXInventorySlotsWidget::ClearSelection()
{
	if (!GridPanel_Item) return;

	const int32 NumChildren = GridPanel_Item->GetChildrenCount();
	for (int32 i = 0; i < NumChildren; i++)
	{
		URXInventorySlotWidget* InventorySlot = Cast<URXInventorySlotWidget>(GridPanel_Item->GetChildAt(i));
		if (InventorySlot && InventorySlot->PressedImage)
		{
			InventorySlot->PressedImage->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void URXInventorySlotsWidget::HandleSlotSelected(URXInventorySlotWidget* SelectedSlot)
{
	// GridPanel에 포함된 모든 슬롯 위젯을 순회하면서,
	// 선택되지 않은 슬롯의 PressedImage를 Hidden으로 설정
	if (!GridPanel_Item) return;

	const int32 NumChildren = GridPanel_Item->GetChildrenCount();
	for (int32 i = 0; i < NumChildren; i++)
	{
		UWidget* ChildWidget = GridPanel_Item->GetChildAt(i);
		URXInventorySlotWidget* InventorySlot = Cast<URXInventorySlotWidget>(ChildWidget);
		if (InventorySlot && InventorySlot != SelectedSlot && InventorySlot->PressedImage)
		{
			InventorySlot->PressedImage->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// 중재자(메인 메뉴 위젯)를 통해 파피루스 그룹의 선택도 해제
	if (MainMenuWidget)
	{
		MainMenuWidget->ClearPapyrusSelection();
	}
}
