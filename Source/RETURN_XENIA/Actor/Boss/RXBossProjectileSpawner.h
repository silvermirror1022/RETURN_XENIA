// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXBossProjectileSpawner.generated.h"

UCLASS()
class RETURN_XENIA_API ARXBossProjectileSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	ARXBossProjectileSpawner();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> RayClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> TargetingFireballClass;

	// 풀링된 프로젝트타일 리스트
	UPROPERTY()
	TArray<AActor*> RayPool;
	UPROPERTY()
	TArray<AActor*> TargetingFireballPool;

	// 프로젝타일 풀 초기화
	void InitializeProjectilePool(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass);

	// 프로젝타일 가져오기 (없으면 새로 생성)
	AActor* GetProjectileFromPool(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass);

	// 프로젝타일 반환
	void ReturnProjectileToPool(AActor* Projectile, TArray<AActor*>& Pool);

	// 특정 종류의 프로젝타일 발사
	UFUNCTION(BlueprintCallable)
	void FireProjectile(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass, FVector SpawnLocation);
};
