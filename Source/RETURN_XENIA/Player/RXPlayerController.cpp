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
	// 
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (const URXInputData* InputData = URXAssetManager::GetAssetByName<URXInputData>("InputData"))
		{
			auto IKey_GameMainMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_IKey);
			auto ESCKey_GamePauseMenuAction = InputData->FindInputActionByTag(RXGameplayTags::Input_Action_ESCKey);

			EnhancedInputComponent->BindAction(IKey_GameMainMenuAction, ETriggerEvent::Started, this, &ARXPlayerController::ActiveGameMainMenu);
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
	}
}

void ARXPlayerController::RespawnPlayerAtCheckPoint() const
{
	if (URXGameInstance* GI = Cast<URXGameInstance>(GetGameInstance()))
	{
		GI->SetGI_Hp(3);
		GI->SetGI_Shield(1);

		// 컨트롤러가 소유한 Pawn(플레이어 캐릭터) 가져오기
		ARXPlayer* PlayerCharacter = Cast<ARXPlayer>(GetPawn());
		if (PlayerCharacter)
		{
			// Player 이동
			PlayerCharacter->SetActorLocationAndRotation(GI->CheckpointTransform.GetLocation(), GI->CheckpointTransform.GetRotation());
			// ARXPlayer 내에 있는 RXPlayerStateComponent를 가져옴

			URXPlayerStatComponent* PlayerStateComp = PlayerCharacter->FindComponentByClass<URXPlayerStatComponent>();
			if (PlayerStateComp)
			{
				PlayerStateComp->InitializeStatComponent();
			}
		}
	}
}
