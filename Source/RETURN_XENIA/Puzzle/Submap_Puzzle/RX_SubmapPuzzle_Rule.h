// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RX_SubmapPuzzle_Rule.generated.h"

UCLASS()
class RETURN_XENIA_API ARX_SubmapPuzzle_Rule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARX_SubmapPuzzle_Rule();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> block;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAlreadyTriggered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ARX_SubmapPuzzle_Observer> observer;


public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
