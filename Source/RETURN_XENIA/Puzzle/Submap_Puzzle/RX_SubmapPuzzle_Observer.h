// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RX_SubmapPuzzle_Observer.generated.h"

UCLASS()
class RETURN_XENIA_API ARX_SubmapPuzzle_Observer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARX_SubmapPuzzle_Observer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION()
	void WrongPath();
};
