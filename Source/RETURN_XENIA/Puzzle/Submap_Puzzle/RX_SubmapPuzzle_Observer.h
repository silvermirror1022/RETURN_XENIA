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
	UPROPERTY()
	TArray<AActor*> tempArray;

	UPROPERTY()
	TObjectPtr<class ARX_SubmapPuzzle_StartPosition> startPosition;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class ARX_SubmapPuzzle_EndPosition> endPosition;

	UPROPERTY()
	TArray<class ARX_SubmapPuzzle_Rule*> puzzleBlocks;

	UPROPERTY()
	TArray<class ARX_SubmapPuzzle_Die*> dieBlocks;

	UPROPERTY()
	TArray<class ARX_SubmapPuzzle_Coin*> coinBlocks;

	UPROPERTY(BlueprintReadOnly)
	int32 coinCount = 0;

	UPROPERTY()
	int32 triggerCoinCount = 0;

	UPROPERTY()
	ACharacter* player;


	
public:
	UFUNCTION()
	void WrongPath();

	UFUNCTION()
	void ClearPath();
};
