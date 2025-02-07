// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RXMapTransitionWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

URXMapTransitionWidget::URXMapTransitionWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void URXMapTransitionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URXMapTransitionWidget::SetMapTransitionImageByName(FName MapName, bool IsKorean)
{
	if (!StageNameImage) return;

	TObjectPtr<UTexture2D>* FoundImage = IsKorean ? KoreanMapImages.Find(MapName) : EnglishMapImages.Find(MapName);

	if (FoundImage && *FoundImage)
	{
		StageNameImage->SetBrushFromTexture(*FoundImage);

		//  텍스처 크기를 가져오기
		FVector2D ImageSize((*FoundImage)->GetSizeX(), (*FoundImage)->GetSizeY());

		// 부모 슬롯 가져오기
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(StageNameImage->Slot))
		{
			CanvasSlot->SetSize(ImageSize);  // 슬롯 크기 설정
		}
	}
}
