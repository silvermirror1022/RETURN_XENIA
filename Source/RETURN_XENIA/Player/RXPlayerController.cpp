// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RXPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Character/RXPlayer.h"
#include "UI/RXHUDWidget.h"

ARXPlayerController::ARXPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}
void ARXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// HUD 위젯을 화면에 추가 -> 에셋정보는 블루프린트에서 캐시
	if (RXHUDWidgetClass) // HSHUDWidgetClass가 유효한지 확인
	{
		ARXHUDWidget = CreateWidget<URXHUDWidget>(GetWorld(), RXHUDWidgetClass);
		if (ARXHUDWidget)
		{
			// HUD를 화면에 추가
			ARXHUDWidget->AddToViewport();
		}
	}
}

void ARXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}