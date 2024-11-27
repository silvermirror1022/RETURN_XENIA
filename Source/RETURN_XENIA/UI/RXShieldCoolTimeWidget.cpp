// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RXShieldCoolTimeWidget.h"
#include "Components/Image.h"
#include "Player/RXPlayerStatComponent.h"

URXShieldCoolTimeWidget::URXShieldCoolTimeWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void URXShieldCoolTimeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AActor* Owner = GetOwningPlayerPawn();
	if (Owner)
	{
		PlayerStatComp = Owner->FindComponentByClass<URXPlayerStatComponent>();
		if (PlayerStatComp)
		{
			// 델리게이트 연결
			PlayerStatComp->OnPlayerShieldSecRegenChanged.AddUObject(this, &URXShieldCoolTimeWidget::UpdateCoolTimeImage);
			PlayerStatComp->OnPlayerShieldFull.AddUObject(this, &URXShieldCoolTimeWidget::UpdateCoolTimeFullImage);
		}
	}
}

void URXShieldCoolTimeWidget::UpdateCoolTimeImage(int32 ImageIdx)
{
	// 이미지 인덱스가 범위를 초과하지 않도록 보호
	if (CoolTimeImages.IsValidIndex(ImageIdx-1))
	{
		if (SecondShowImage)
		{
			// 이미지 브러시 업데이트
			SecondShowImage->SetBrushFromTexture(CoolTimeImages[ImageIdx-1]);
		}
	}
}

void URXShieldCoolTimeWidget::UpdateCoolTimeFullImage()
{
	if (SecondShowImage)
	{
		// 힐링 아이템 획득시 브러시 업데이트
		SecondShowImage->SetBrushFromTexture(CoolTimeImages[7]);
	}
}
