// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/RXPapyrusSlotsWidget.h"
#include "System/RXGameInstance.h"
#include "Components/UniformGridPanel.h"
#include "UI/RXMainMenuWidget.h"
#include "UI/Inventory/RXInventorySlotWidget.h"
#include "Components/Image.h"

URXPapyrusSlotsWidget::URXPapyrusSlotsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URXPapyrusSlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 계층에서 부모 MainMenuWidget 검색
	MainMenuWidget = GetTypedOuter<URXMainMenuWidget>();

	URXGameInstance* GI = GetWorld()->GetGameInstance<URXGameInstance>();
	if (!GI || !GridPanel_Item) return;

	// 파피루스 아이템 이름들
	TArray<FString> PapyrusItemNames = { TEXT("Papyrus1"), TEXT("Papyrus2"), TEXT("Papyrus3") };

	// 파피루스 슬롯은 가로 3개, 세로 1행으로 구성
	constexpr int X_COUNT = 3;
	constexpr int Y_COUNT = 1;
	int32 CurrentItemIndex = 0;

	// 획득된 파피루스 아이템만 필터링
	TArray<int32> AcquiredItemIndices;
	for (int32 i = 0; i < PapyrusItemNames.Num(); i++)
	{
		if (GI->IsItemStatusAcquired(PapyrusItemNames[i]))
		{
			AcquiredItemIndices.Add(i);
		}
	}

	// GridPanel에 슬롯 추가
	for (int32 Y = 0; Y < Y_COUNT; Y++)
	{
		for (int32 X = 0; X < X_COUNT; X++)
		{
			// 획득된 아이템 인덱스 범위를 초과하면 빈 슬롯 생성
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
				// 획득된 파피루스 아이템 추가
				int32 ItemIndex = AcquiredItemIndices[CurrentItemIndex];
				if (ItemIndex < ItemClass.Num())
				{
					URXInventorySlotWidget* SlotWidget = CreateWidget<URXInventorySlotWidget>(GetOwningPlayer(), ItemClass[ItemIndex]);
					SlotWidget->SetMainMenuWidget(MainMenuWidget);

					GridPanel_Item->AddChildToUniformGrid(SlotWidget, Y, X);

					// 각 슬롯 위젯의 델리게이트에 핸들러 바인딩
					SlotWidget->OnSlotSelected.AddDynamic(this, &URXPapyrusSlotsWidget::HandleSlotSelected);

					CurrentItemIndex++; // 아이템 추가 시 인덱스 증가
				}
			}
		}
	}

	/*// GridPanel에 슬롯이 하나라도 있으면 첫 번째 슬롯을 자동으로 선택
	if (GridPanel_Item->GetChildrenCount() > 0)
	{
		URXInventorySlotWidget* FirstSlot = Cast<URXInventorySlotWidget>(GridPanel_Item->GetChildAt(0));
		if (FirstSlot && FirstSlot->OwnImage) // 아이템 이미지가 존재하면
		{
			FirstSlot->ReplaceParentImageWithOwn();
		}
	}*/
}

void URXPapyrusSlotsWidget::ClearSelection()
{
	if (!GridPanel_Item) return;

	const int32 NumChildren = GridPanel_Item->GetChildrenCount();
	for (int32 i = 0; i < NumChildren; i++)
	{
		URXInventorySlotWidget* PapyrusSlot = Cast<URXInventorySlotWidget>(GridPanel_Item->GetChildAt(i));
		if (PapyrusSlot && PapyrusSlot->PressedImage)
		{
			PapyrusSlot->PressedImage->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void URXPapyrusSlotsWidget::HandleSlotSelected(URXInventorySlotWidget* SelectedSlot)
{
	// GridPanel에 포함된 모든 슬롯 위젯을 순회하며,
	// 선택되지 않은 슬롯의 PressedImage를 Hidden 처리
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

	// 중재자(메인 메뉴 위젯)를 통해 인벤토리 그룹의 선택도 해제
	if (MainMenuWidget)
	{
		MainMenuWidget->ClearInventorySelection();
	}
}
