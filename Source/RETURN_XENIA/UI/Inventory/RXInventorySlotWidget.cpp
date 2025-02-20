// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/RXInventorySlotWidget.h"
#include "UI/RXMainMenuWidget.h"
#include "Components/Image.h"
#include "Components/Button.h" 
#include "Components/SizeBox.h"
#include "Engine/Texture2D.h"
#include "System/RXGameInstance.h"

URXInventorySlotWidget::URXInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URXInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox->SetWidthOverride(148.0f);
	SizeBox->SetHeightOverride(148.0f);

	// 처음엔 PressedImage를 숨김으로 설정
	if (PressedImage)
	{
		PressedImage->SetVisibility(ESlateVisibility::Hidden);
	}

	//버튼 클릭시 다이나믹 ReplaceParentImageWithOwn() 연결 함수
	if (Button) 
	{
		Button->OnPressed.AddDynamic(this, &URXInventorySlotWidget::ReplaceParentImageWithOwn);
	}

}
void URXInventorySlotWidget::SetMainMenuWidget(URXMainMenuWidget* InMainMenuWidget)
{
	MainMenuWidget = InMainMenuWidget;
}

void URXInventorySlotWidget::UpdateDescriptionImages(bool bIsKorean)
{
	if (!MainMenuWidget)
	{
		return;
	}

	// 언어에 따라 적절한 설명 이미지에 브러시를 적용
	FSlateBrush Brush;
	if (bIsKorean)
	{
		if (OwnDescKRImage)
		{
			Brush.SetResourceObject(OwnDescKRImage);
			MainMenuWidget->Img_ItemDesc_KR->SetBrush(Brush);
			MainMenuWidget->Img_ItemDesc_KR->SetVisibility(ESlateVisibility::Visible);
		}
		// 영어 설명 이미지는 히든 처리
		MainMenuWidget->Img_ItemDesc_EN->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		if (OwnDescENImage)
		{
			Brush.SetResourceObject(OwnDescENImage);
			MainMenuWidget->Img_ItemDesc_EN->SetBrush(Brush);
			MainMenuWidget->Img_ItemDesc_EN->SetVisibility(ESlateVisibility::Visible);
		}
		// 한국어 설명 이미지는 히튼 처리
		MainMenuWidget->Img_ItemDesc_KR->SetVisibility(ESlateVisibility::Hidden);
	}

	// 아이템 타입이 HintPaper인 경우 버튼을 보이고 활성화
	if (ItemType == FName("HintPaper"))
	{
		MainMenuWidget->Btn_NoteDesc->SetVisibility(ESlateVisibility::Visible);
		MainMenuWidget->Btn_NoteDesc->SetIsEnabled(true);
	}
	else
	{
		MainMenuWidget->Btn_NoteDesc->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidget->Btn_NoteDesc->SetIsEnabled(false);
	}
}

void URXInventorySlotWidget::ReplaceParentImageWithOwn()
{
	if (URXGameInstance* GI = GetWorld()->GetGameInstance<URXGameInstance>())
	{
		bool bIsKorean = GI->bIsKorean; 
		UpdateDescriptionImages(bIsKorean);
	}

	if (MainMenuWidget && MainMenuWidget->ItemInfoImage && OwnImage)
	{
		// FSlateBrush를 만들어서 텍스처를 설정
		FSlateBrush Brush;
		Brush.SetResourceObject(OwnImage);

		// MainMenuWidget의 ItemInfoImage에 Brush 설정
		MainMenuWidget->ItemInfoImage->SetBrush(Brush);
		MainMenuWidget->ItemInfoImage->SetVisibility(ESlateVisibility::Visible);
	}

	// 이 슬롯의 PressedImage를 Visible로 전환 -> 자기 자신 선택 표시
	if (PressedImage)
	{
		PressedImage->SetVisibility(ESlateVisibility::Visible);
	}

	// 슬롯 선택 이벤트 발생: 부모가 이 슬롯을 제외한 다른 슬롯의 PressedImage를 숨길 수 있도록 알림
	OnSlotSelected.Broadcast(this);
}

