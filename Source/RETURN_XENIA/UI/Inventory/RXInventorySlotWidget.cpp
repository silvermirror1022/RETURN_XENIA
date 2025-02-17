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
	// 타입에 따라 설명 이미지의 가시성을 설정
	if (ItemType == FName("HintPaper"))
	{
		if (bIsKorean)
		{
			MainMenuWidget->Img_Note_DescKR->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidget->Img_Note_DescEN->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Knotletter_DescKR->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Knotletter_DescEN->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			MainMenuWidget->Img_Note_DescEN->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidget->Img_Note_DescKR->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Knotletter_DescKR->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Knotletter_DescEN->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else if (ItemType == FName("KnotChar"))
	{
		if (bIsKorean)
		{
			MainMenuWidget->Img_Knotletter_DescKR->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidget->Img_Knotletter_DescEN->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Note_DescEN->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Note_DescKR->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			MainMenuWidget->Img_Knotletter_DescEN->SetVisibility(ESlateVisibility::Visible);
			MainMenuWidget->Img_Knotletter_DescKR->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Note_DescEN->SetVisibility(ESlateVisibility::Hidden);
			MainMenuWidget->Img_Note_DescKR->SetVisibility(ESlateVisibility::Hidden);
		}
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

