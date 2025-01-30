// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXBossFBPoolManager.generated.h"

UCLASS()
class RETURN_XENIA_API ARXBossFBPoolManager : public AActor
{
	GENERATED_BODY()

public:
	ARXBossFBPoolManager();

protected:
	virtual void BeginPlay() override;

public:
	void InitializePool(TSubclassOf<class ARXBossFixedFireball> ActorClass, int32 PoolSize);
	ARXBossFixedFireball* GetPooledActor();
	void FireInCircle(FVector Center, float ZHeight);

	UFUNCTION(BlueprintCallable)
	void FireInCircleAt190(FVector Center);
	UFUNCTION(BlueprintCallable)
	void FireInCircleAt300(FVector Center);

private:
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<ARXBossFixedFireball> PooledActorClass;

	UPROPERTY()
	TArray<ARXBossFixedFireball*> ObjectPool;

	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 PoolSize = 200;
};