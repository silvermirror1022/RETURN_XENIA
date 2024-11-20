// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RX_RollingPuzzle.generated.h"

USTRUCT(BlueprintType)
struct FRollStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName combineCircleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 rollCount;
};

UCLASS()
class RETURN_XENIA_API ARX_RollingPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARX_RollingPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// s size circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> smallCircle;

	// m size circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> middleCircle;

	// l size circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> largeCircle;

	// x size circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> extraLargeCircle;

	// if attach with player, change camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UCameraComponent> puzzleCamera;

	// puzzle target score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleSystem")
	int32 totalScore = 0;

	// if clear, active event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleSystem")
	TObjectPtr<class ARX_Parent_CustomEvent> customEvent = nullptr;

	// if clear, drop item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleSystem")
	TObjectPtr<AActor> dropItem = nullptr;

	// move with small circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleSystem")
	TArray<FRollStruct> rollWithSmall;

	// move with middle circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleSystem")
	TArray<FRollStruct> rollWithMiddle;

	// move with large circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleSystem")
	TArray<FRollStruct> rollWithLarge;

	// move with extra large circle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleSystem")
	TArray<FRollStruct> rollWithExtraLarge;


	// moving circle
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> activeCircle;

	// to find shortest location
	UPROPERTY()
	float shortestLocation;

	// socket name
	UPROPERTY()
	FName shortestLocationName;

	UPROPERTY()
	bool isReady = false;

	UPROPERTY()
	bool isAttachPlayer = false;

	UPROPERTY()
	bool isRolling = false;

	UPROPERTY()
	bool isClear = false;

	UPROPERTY()
	int32 rollCount = 0;

	UPROPERTY()
	int32 smallScore = 0;

	UPROPERTY()
	int32 middleScore = 0;

	UPROPERTY()
	int32 largeScore = 0;

	UPROPERTY()
	int32 extraLargeScore = 0;

	UPROPERTY()
	int32 nowScore = 0;




};
