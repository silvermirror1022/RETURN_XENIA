// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RXMapTransitionWidget.h"
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
	}
}
