// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle/Submap_Puzzle/RX_SubmapPuzzle_Rule.h"
#include "RX_SubmapPuzzle_EndPosition.generated.h"

/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARX_SubmapPuzzle_EndPosition : public ARX_SubmapPuzzle_Rule
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARX_SubmapPuzzle_EndPosition();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> endBlock;

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
