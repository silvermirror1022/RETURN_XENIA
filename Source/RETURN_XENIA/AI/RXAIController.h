// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RXAIController.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARXAIController : public AAIController
{
	GENERATED_BODY()
public:
	ARXAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void OnPossess(APawn* InPawn) override;
};
