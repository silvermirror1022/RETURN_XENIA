// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RXPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Character/RXPlayer.h"
#include "UI/RXHUDWidget.h"
#include "System/RXGameInstance.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "System/RXAssetManager.h"
#include "Data/RXInputData.h"
#include "RXGameplayTags.h"
#include "RXDebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/RXPlayerStart.h"

ARXPlayerController::ARXPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// UI 변수들 초기화
	bIsPauseMenuUIActive = false;
	bIsMainMenuUIActive = false;
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
	//SetInputMode(FInputModeGameAndUI()); // UI와 게임 모드 둘 다 활성화
	//bShowMouseCursor = true;              // 마우스 커서 표시

	SpawnPlayerToDestination();
}

void ARXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI에 대한 인풋 초기화는 플레이어 컨트롤러에서 관리 (기본적 이동과 상호작용은 Player에서 관리)

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
		{
			auto TabKey_GameMainMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_TabKey);
			auto ESCKey_GamePauseMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_ESCKey);

			EnhancedInputComponent->BindAction(TabKey_GameMainMenuAction, ETriggerEvent::Started, this, &ARXPlayerController::ActiveGameMainMenu);
			EnhancedInputComponent->BindAction(ESCKey_GamePauseMenuAction, ETriggerEvent::Started, this, &ARXPlayerController::ActiveGamePauseMenu);
		}
	}
}
bool ARXPlayerController::CheckUIActiveState()
{
	return (bIsPauseMenuUIActive || bIsMainMenuUIActive);
}
void ARXPlayerController::ActiveGameMainMenu()
{
	if (CheckUIActiveState()) return;

	bIsMainMenuUIActive = true;

	// 게임메뉴 UI를 띄우는 함수 BY TAB KEY
	if (RXGameMainMenuWidgetClass) 
	{
		ARXGameMainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), RXGameMainMenuWidgetClass);
		if (ARXGameMainMenuWidget)
		{
			ARXGameMainMenuWidget->AddToViewport();

		}
	}
}

void ARXPlayerController::ActiveGamePauseMenu()
{
	if (CheckUIActiveState()) return;

	bIsPauseMenuUIActive = true;

	// 게임팝업 UI를 띄우는 함수 BY ESC KEY
	if (RXGamePauseMenuWidgetClass)
	{
		ARXGamePauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), RXGamePauseMenuWidgetClass);
		if (ARXGamePauseMenuWidget)
		{
			ARXGamePauseMenuWidget->AddToViewport();
		}
	}
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


