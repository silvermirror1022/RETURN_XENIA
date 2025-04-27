// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RXPlayerController.h"
#include "UI/RXHUDWidget.h"
#include "System/RXGameInstance.h"
#include "EnhancedInputComponent.h"
#include "System/RXAssetManager.h"
#include "Data/RXInputData.h"
#include "RXGameplayTags.h"
#include "Character/RXPlayer.h"
#include "Player/RXPlayerStatComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/RXPlayerStart.h"
#include "UI/RXMainMenuWidget.h"
#include "RXDebugHelper.h"
#include "UI/RXNewItemWidget.h"


ARXPlayerController::ARXPlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// UI 변수들 초기화
	bIsPauseMenuUIActive = false;
	bIsMainMenuUIActive = false;
	bIsInDialogue = false;
}
void ARXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// HUD 위젯을 화면에 추가 -> 에셋정보는 블루프린트에서 캐시
	if (RXHUDWidgetClass) // RXHUDWidgetClass가 유효한지 확인
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
	// 
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
		{
			auto IKey_GameMainMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_IKey);
			auto MapKey_GameMapMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_MapKey);
			auto ESCKey_GamePauseMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_ESCKey);

			EnhancedInputComponent->BindAction(IKey_GameMainMenuAction, ETriggerEvent::Started, this, &ARXPlayerController::ActiveGameMainMenu);
			EnhancedInputComponent->BindAction(MapKey_GameMapMenuAction, ETriggerEvent::Started, this, &ARXPlayerController::ActiveGameMapMenu);
			EnhancedInputComponent->BindAction(ESCKey_GamePauseMenuAction, ETriggerEvent::Started, this, &ARXPlayerController::HandleEscapeKeyPressed);


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
	
	// 게임메뉴 UI Item를 띄우는 함수 BY I KEY
	if (RXGameMainMenuWidgetClass) 
	{
		ARXGameMainMenuWidget = CreateWidget<URXMainMenuWidget>(GetWorld(), RXGameMainMenuWidgetClass);
		if (ARXGameMainMenuWidget)
		{
			ARXGameMainMenuWidget->AddToViewport();
		}
	}
}

void ARXPlayerController::ActiveGameMapMenu()
{
	if (CheckUIActiveState()) return;

	bIsMainMenuUIActive = true;

	// 게임메뉴 UI MAP를 띄우는 함수 BY M KEY
	if (RXGameMainMenuWidgetClass)
	{
		ARXGameMainMenuWidget = CreateWidget<URXMainMenuWidget>(GetWorld(), RXGameMainMenuWidgetClass);
		if (ARXGameMainMenuWidget)
		{
			ARXGameMainMenuWidget->AddToViewport();
			ARXGameMainMenuWidget->InitToGameMapMenu();
		}
	}
}

void ARXPlayerController::ActiveGamePauseMenu()
{
	if (CheckUIActiveState() || bIsInDialogue) return;  //대화중이라면 옵션창을 못띄우게해 언어설정을 막도록 예외처리

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

void ARXPlayerController::HandleEscapeKeyPressed()
{
	if (UIWidgetStack.Num() > 0)
	{
		RemoveUIWidgetFromStack(); // UI 닫기
	}
	else
	{
		ActiveGamePauseMenu(); // 일시정지 메뉴 띄우기
	}
}

void ARXPlayerController::SpawnPlayerToDestination() const
{
	if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
	{
		// 체크포인트가 없다면 기존 DestinationTag 로직 실행
		FGameplayTag DestinationTag = GI->CurrentDestinationTag;
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARXPlayerStart::StaticClass(), PlayerStarts);

		for (AActor* Actor : PlayerStarts)
		{
			ARXPlayerStart* PlayerStart = Cast<ARXPlayerStart>(Actor);
			if (PlayerStart && PlayerStart->StartTag.MatchesTag(DestinationTag))
			{
				if (APawn* ControlledPawn = GetPawn())
				{
					ControlledPawn->SetActorLocation(PlayerStart->GetActorLocation());
					ControlledPawn->SetActorRotation(PlayerStart->GetActorRotation());
				}
				break;
			}
		}

		if(GI->bIsContinueGame)
		{   // 컨티뉴게임으로 로드할 경우에는 플레이어스타트가 아닌 커스텀 트랜스폼으로 이동하여 스폰
			if (ARXPlayer* PlayerCharacter = Cast<ARXPlayer>(GetPawn()))
			{
				PlayerCharacter->SetActorLocation(GI->CheckpointTransform.GetLocation());
			}
			// 1.5초 후 bIsContinueGame = false 처리
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [GI]()
				{
					GI->bIsContinueGame = false;
				}, 1.5f, false);
		}
	}
}

void ARXPlayerController::RespawnPlayerAtCheckPoint() const
{
	if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
	{
		GI->SetGI_Hp(3);
		GI->SetGI_Shield(1);

		// 컨트롤러가 소유한 Pawn(플레이어 캐릭터) 가져오기
		if (ARXPlayer* PlayerCharacter = Cast<ARXPlayer>(GetPawn()))
		{
			// Player 이동
			PlayerCharacter->SetActorLocationAndRotation(GI->CheckpointTransform.GetLocation(), GI->CheckpointTransform.GetRotation());
			// ARXPlayer 내에 있는 RXPlayerStateComponent를 가져옴

			URXPlayerStatComponent* PlayerStatComp = PlayerCharacter->FindComponentByClass<URXPlayerStatComponent>();
			if (PlayerStatComp)
			{
				PlayerStatComp->InitializeStatComponent();
			}
		}
	}
}

void ARXPlayerController::RespawnFallingPlayerAtCheckPoint() const
{
	if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
	{
		// 컨트롤러가 소유한 Pawn(플레이어 캐릭터) 가져오기
		if (ARXPlayer* PlayerCharacter = Cast<ARXPlayer>(GetPawn()))
		{
			// Player 이동
			PlayerCharacter->SetActorLocationAndRotation(GI->CheckpointTransform.GetLocation(), GI->CheckpointTransform.GetRotation());
		}
	}
}

void ARXPlayerController::RemoveUIWidgetFromStack()
{
	// UI 지우기 함수
	if (UIWidgetStack.Num() == 0)
		return;

	UUserWidget* TopWidget = UIWidgetStack.Pop();

	if (TopWidget)
	{
		// 만약 TopWidget이 NewItemWidget 타입이면 CloseWidget 호출
		if (URXNewItemWidget* NewItemWidget = Cast<URXNewItemWidget>(TopWidget))
		{
			NewItemWidget->CloseWidget();
		}

		TopWidget->RemoveFromParent();
	}

	// 스택에 더 이상 위젯이 없다면, UI 상태 초기화
	if (UIWidgetStack.Num() == 0)
	{
		UGameplayStatics::SetGamePaused(this, false);
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
		bIsMainMenuUIActive = false;
		bIsPauseMenuUIActive = false;
	}
	else
	{
		// 혹시 남은 위젯이 있으면 포커스 위젯
		UUserWidget* NewTopWidget = UIWidgetStack.Last();
		if (NewTopWidget)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(NewTopWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);

			SetInputMode(InputMode);
			bShowMouseCursor = true;
		}
	}
}

void ARXPlayerController::PushUIWidgetToStack(UUserWidget* NewWidget)
{
	if (!NewWidget) return;
	UIWidgetStack.Add(NewWidget);

}

void ARXPlayerController::RemoveUIWidgetOnlyStack(UUserWidget* NewWidget)
{
	UUserWidget* TopWidget = UIWidgetStack.Pop();
	if (TopWidget)
	{
		TopWidget->RemoveFromParent();
	}

}
