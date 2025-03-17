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
	void InitializePool(TSubclassOf<class ARXBossFixedFireball> ActorClass1, TSubclassOf<class ARXBossFixedFireball> ActorClass2, int32 PoolSize);
	ARXBossFixedFireball* GetPooledActor(bool bUseFirstPool); // 특정 풀에서 가져오기
	void FireTowardsPlayer(FVector Center, float ZHeight, AActor* Target);


	UFUNCTION(BlueprintCallable)
	void FireAtPlayerFrom120(FVector Center, AActor* Target);
	UFUNCTION(BlueprintCallable)
	void FireAtPlayerFrom150(FVector Center, AActor* Target);

private:
	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<ARXBossFixedFireball> PooledActorClass;   // 첫 번째 타입(빨강)

	UPROPERTY(EditAnywhere, Category = "Pooling")
	TSubclassOf<ARXBossFixedFireball> PooledActorClass2;  // 두 번째 타입(보라)

	UPROPERTY()
	TArray<ARXBossFixedFireball*> ObjectPool1; // 첫 번째 풀

	UPROPERTY()
	TArray<ARXBossFixedFireball*> ObjectPool2; // 두 번째 풀

	UPROPERTY(EditAnywhere, Category = "Pooling")
	int32 PoolSize = 200;
};