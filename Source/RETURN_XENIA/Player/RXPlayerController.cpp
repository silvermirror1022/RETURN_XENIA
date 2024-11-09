// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RXPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Character/RXPlayer.h"
#include "UI/RXHUDWidget.h"
#include "System/RXGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/RXPlayerStart.h"

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

	SpawnPlayerToDestination();
}

void ARXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ARXPlayerController::SpawnPlayerToDestination()
{
	// 게임 인스턴스에서 DestinationTag 가져오기
	if (URXGameInstance* GameInstance = Cast<URXGameInstance>(GetGameInstance()))
	{
		FGameplayTag DestinationTag = GameInstance->CurrentDestinationTag;

		// 해당 DestinationTag와 일치하는 PlayerStart 찾기
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARXPlayerStart::StaticClass(), PlayerStarts);

		for (AActor* Actor : PlayerStarts)
		{
			ARXPlayerStart* PlayerStart = Cast<ARXPlayerStart>(Actor);
			if (PlayerStart && PlayerStart->StartTag.MatchesTag(DestinationTag))
			{
				// 태그가 일치하는 PlayerStart 위치로 플레이어 이동
				if (APawn* ControlledPawn = GetPawn())
				{
					ControlledPawn->SetActorLocation(PlayerStart->GetActorLocation());
				}
				break;
			}
		}
	}
}
