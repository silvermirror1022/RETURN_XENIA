// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/RXInventorySlotWidget.h"
#include "UI/RXMainMenuWidget.h"
#include "Components/Image.h"
#include "Components/Button.h" 
#include "Engine/Texture2D.h"

URXInventorySlotWidget::URXInventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URXInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//버튼 클릭시 다이나믹 ReplaceParentImageWithOwn() 연결 함수
	if (Button) 
	{
		Button->OnClicked.AddDynamic(this, &URXInventorySlotWidget::ReplaceParentImageWithOwn);
	}
}
void URXInventorySlotWidget::SetMainMenuWidget(URXMainMenuWidget* InMainMenuWidget)
{
	MainMenuWidget = InMainMenuWidget;
}

void URXInventorySlotWidget::ReplaceParentImageWithOwn()
{
	if (MainMenuWidget && MainMenuWidget->ItemInfoImage && OwnImage)
	{
		// FSlateBrush를 만들어서 텍스처를 설정
		FSlateBrush Brush;
		Brush.SetResourceObject(OwnImage);

		// MainMenuWidget의 ItemInfoImage에 Brush 설정
		MainMenuWidget->ItemInfoImage->SetBrush(Brush);
		UE_LOG(LogTemp, Warning, TEXT("Success"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Failed"));
}

