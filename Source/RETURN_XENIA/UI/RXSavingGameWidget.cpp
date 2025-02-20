// Fill out your copyright notice in the Description page of Project Settings.


#include "RXSavingGameWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "TimerManager.h"
#include "Engine/World.h"

URXSavingGameWidget::URXSavingGameWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void URXSavingGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 초기 인덱스 설정
	CurrentIndexCircle = 0;
	CurrentIndexText = 0;

	// 초기 텍스처 설정
	if (Image_LoadingCircle && LoadingCircleTextures.Num() > 0)
	{
		Image_LoadingCircle->SetBrushFromTexture(LoadingCircleTextures[0]);
	}

	if (Image_LoadingText && LoadingTextTextures.Num() > 0)
	{
		Image_LoadingText->SetBrushFromTexture(LoadingTextTextures[0]);
	}

	// 타이머 시작: 텍스처 배열에 따라 변경 간격 계산
	if (LoadingCircleTextures.Num() > 0)
	{
		float IntervalCircle = LoadingCircleDuration / LoadingCircleTextures.Num();
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandleCircle, this, &URXSavingGameWidget::UpdateLoadingCircleImage, IntervalCircle, true);
		}
	}

	if (LoadingTextTextures.Num() > 0)
	{
		float IntervalText = LoadingTextDuration / LoadingTextTextures.Num();
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandleText, this, &URXSavingGameWidget::UpdateLoadingTextImage, IntervalText, true);
		}
	}
}

void URXSavingGameWidget::UpdateLoadingCircleImage()
{
	if (!Image_LoadingCircle || LoadingCircleTextures.Num() == 0)
	{
		return;
	}

	// 다음 텍스처 인덱스로 순환
	CurrentIndexCircle = (CurrentIndexCircle + 1) % LoadingCircleTextures.Num();
	Image_LoadingCircle->SetBrushFromTexture(LoadingCircleTextures[CurrentIndexCircle]);
}

void URXSavingGameWidget::UpdateLoadingTextImage()
{
	if (!Image_LoadingText || LoadingTextTextures.Num() == 0)
	{
		return;
	}

	CurrentIndexText = (CurrentIndexText + 1) % LoadingTextTextures.Num();
	Image_LoadingText->SetBrushFromTexture(LoadingTextTextures[CurrentIndexText]);
}