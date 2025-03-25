// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/RXMainMenuWidget.h"
#include "Components/Image.h"
#include "UI/Inventory/RXInventorySlotsWidget.h"
#include "UI/Inventory/RXPapyrusSlotsWidget.h"

URXMainMenuWidget::URXMainMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URXMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

// 모든 PressedImage를 숨기는 함수
void URXMainMenuWidget::ResetAllPressedImages() const
{
  
	TArray<TObjectPtr<UImage>> AllPressedImages = {
		Ch1_PressedImg_EN, Ch1_PressedImg_KR,
        Ch2_PressedImg_EN, Ch2_PressedImg_KR,
        Ch3_PressedImg_EN, Ch3_PressedImg_KR,
        Ch4_PressedImg_EN, Ch4_PressedImg_KR,
        Ch5_PressedImg_EN, Ch5_PressedImg_KR
	};

	for (UImage* Img : AllPressedImages)
	{
		if (Img)
		{
			Img->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void URXMainMenuWidget::InitToGameMapMenu_Implementation()
{
    // Implementation in Blueprint
    // 해당 함수는 M Key를 통해 맵메인메뉴를 킬 때 맵 매뉴로 초기화해주는 함수
    // 블루프린트에서 Map버튼클릭했을 경우 로직 사용
}

void URXMainMenuWidget::OnCh1BtnPressed(bool bIsKorean)
{
    ResetAllPressedImages();
    if (bIsKorean && Ch1_PressedImg_KR)
    {
        Ch1_PressedImg_KR->SetVisibility(ESlateVisibility::Visible);
    }
    else if (!bIsKorean && Ch1_PressedImg_EN)
    {
        Ch1_PressedImg_EN->SetVisibility(ESlateVisibility::Visible);
    }
}

void URXMainMenuWidget::OnCh2BtnPressed(bool bIsKorean)
{
    ResetAllPressedImages();
    if (bIsKorean && Ch2_PressedImg_KR)
    {
        Ch2_PressedImg_KR->SetVisibility(ESlateVisibility::Visible);
    }
    else if (!bIsKorean && Ch2_PressedImg_EN)
    {
        Ch2_PressedImg_EN->SetVisibility(ESlateVisibility::Visible);
    }
}

void URXMainMenuWidget::OnCh3BtnPressed(bool bIsKorean)
{
    ResetAllPressedImages();
    if (bIsKorean && Ch3_PressedImg_KR)
    {
        Ch3_PressedImg_KR->SetVisibility(ESlateVisibility::Visible);
    }
    else if (!bIsKorean && Ch3_PressedImg_EN)
    {
        Ch3_PressedImg_EN->SetVisibility(ESlateVisibility::Visible);
    }
}

void URXMainMenuWidget::OnCh4BtnPressed(bool bIsKorean)
{
    ResetAllPressedImages();
    if (bIsKorean && Ch4_PressedImg_KR)
    {
        Ch4_PressedImg_KR->SetVisibility(ESlateVisibility::Visible);
    }
    else if (!bIsKorean && Ch4_PressedImg_EN)
    {
        Ch4_PressedImg_EN->SetVisibility(ESlateVisibility::Visible);
    }
}

void URXMainMenuWidget::OnCh5BtnPressed(bool bIsKorean)
{
    ResetAllPressedImages();
    if (bIsKorean && Ch5_PressedImg_KR)
    {
        Ch5_PressedImg_KR->SetVisibility(ESlateVisibility::Visible);
    }
    else if (!bIsKorean && Ch5_PressedImg_EN)
    {
        Ch5_PressedImg_EN->SetVisibility(ESlateVisibility::Visible);
    }
}

void URXMainMenuWidget::ClearPapyrusSelection()
{
    if (WBP_PapyrusSlotsWidget) // URXPapyrusSlotsWidget의 참조
    {
        WBP_PapyrusSlotsWidget->ClearSelection();
    }
}

void URXMainMenuWidget::ClearInventorySelection()
{
    if (WBP_InventorySlotsWidget) // URXInventorySlotsWidget의 참조
    {
        WBP_InventorySlotsWidget->ClearSelection();
    }
}
