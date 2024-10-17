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
	TSubclassOf<class URXHUDWidget> RXHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class URXHUDWidget> ARXHUDWidget;
};
