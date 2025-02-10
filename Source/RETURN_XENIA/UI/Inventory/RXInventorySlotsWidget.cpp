// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/RXInventorySlotsWidget.h"
#include "System/RXGameInstance.h"
#include "Components/UniformGridPanel.h"
#include "UI/RXMainMenuWidget.h"
#include "UI/Inventory/RXInventorySlotWidget.h"

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
		TEXT("KnotChar2F_1"), TEXT("KnotChar2F_2"),TEXT("KnotChar2F_3"), TEXT("Heart"), TEXT("HintPaper")};

	constexpr int X_COUNT = 3;
	constexpr int Y_COUNT = 4;
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

					CurrentItemIndex++; // 아이템 추가 시 인덱스 증가
				}
			}
		}
	}
}
