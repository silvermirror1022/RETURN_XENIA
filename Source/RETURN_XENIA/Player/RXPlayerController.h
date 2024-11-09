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

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ARXPlayer> RXPlayer;

	//HUD SECTION
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class URXHUDWidget> RXHUDWidgetClass; // 플레이어에게 보일 HUD UI 위젯 BP

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class URXHUDWidget> ARXHUDWidget; // HUD UI 포인터

public:
	// 컨트롤러가 플레이어 포세스할 때 항상 저장한 위치로 스폰을 위한 함수
	void SpawnPlayerToDestination();
};
