// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RXPauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API URXPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExitUserWidget")
	TSubclassOf<class UUserWidget> ExitUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionUserWidget")
	TSubclassOf<class UUserWidget> OptionUserWidget;
};
