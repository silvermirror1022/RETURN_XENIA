// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RXPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARXPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	//HUD SECTION
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class URXHUDWidget> RXHUDWidgetClass; // 플레이어에게 보일 HUD UI 위젯 BP

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URXHUDWidget> ARXHUDWidget; // HUD UI 포인터

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainMenu")
	TSubclassOf<class URXMainMenuWidget> RXGameMainMenuWidgetClass; // 플레이어에게 보일 게임메인메뉴 UI 위젯 BP

	UPROPERTY()
	TObjectPtr<URXMainMenuWidget> ARXGameMainMenuWidget; // 메인메뉴 UI 포인터

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PauseMenu")
	TSubclassOf<UUserWidget> RXGamePauseMenuWidgetClass; // 플레이어에게 보일 게임팝업메뉴 UI 위젯 BP

	UPROPERTY()
	TObjectPtr<UUserWidget> ARXGamePauseMenuWidget; // 퍼즈매뉴 UI 포인터

public:

	void ActiveGameMainMenu();
	void ActiveGameMapMenu();
	void ActiveGamePauseMenu();
	
	UFUNCTION(BlueprintCallable)
	inline void InActiveGameMainMenu() { bIsMainMenuUIActive = false; }
	UFUNCTION(BlueprintCallable)
	inline void InActiveGamePauseMenu() { bIsPauseMenuUIActive = false; }

	void HandleEscapeKeyPressed();
public:
	// 컨트롤러가 플레이어 포세스할 때 항상 저장한 위치로 스폰을 위한 함수
	void SpawnPlayerToDestination() const;

	// 플레이어 hp 0 이되어 사망시 처리해야할 함수
	UFUNCTION(BlueprintCallable)
	void RespawnPlayerAtCheckPoint() const;

	// 플레이어 낙사시 처리해야할 함수
	UFUNCTION(BlueprintCallable)
	void RespawnFallingPlayerAtCheckPoint() const;

	// UI 위젯 제거함수(By ESC Key)
	UFUNCTION(BlueprintCallable)
	void RemoveUIWidgetFromStack();

	// UI 위젯 ADDViewPort시 추가함수
	UFUNCTION(BlueprintCallable)
	void PushUIWidgetToStack(UUserWidget* NewWidget);

	UFUNCTION(BlueprintCallable)
	void RemoveUIWidgetOnlyStack(UUserWidget* NewWidget);

	bool CheckUIActiveState(); // UI 활성화 추적 함수
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	uint8 bIsPauseMenuUIActive : 1; // 팝업 UI 활성화상태 BOOL 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	uint8 bIsMainMenuUIActive : 1; // 메인메뉴 UI 활성화상태 BOOL 변수

	void SetDialogueState(uint8 bInDialogue) { bIsInDialogue = bInDialogue; }
	uint8 bIsInDialogue : 1; // 대화중인지 체크 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite); // 위젯스택
	TArray<TObjectPtr<UUserWidget>> UIWidgetStack;

};
