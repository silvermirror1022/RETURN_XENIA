// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXRockSpawner.generated.h"

class ARXRockBase;

UCLASS()
class RETURN_XENIA_API ARXRockSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ARXRockSpawner();

protected:
	virtual void BeginPlay() override;

public:
	
	// 바위를 발사하는 함수
	UFUNCTION(BlueprintCallable)
	void SpawnRock();

	// 바위를 모두 비활성화하는 함수
	UFUNCTION(BlueprintCallable)
	void DeactivateAllRocks();

	// 바위를 다시 풀로 반환하는 함수
	void ReturnRockToPool(ARXRockBase* Rock);

	// Rock 오브젝트 풀
	UPROPERTY()
	TArray<ARXRockBase*> RockPool;

	// 최대 보유할 Rock 개수(기본 4)
	UPROPERTY(EditAnywhere, Category = "RockSetting")
	int32 MaxRockCount = 8;

	// 바위 클래스 (스폰할 클래스설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RockSetting")
	TSubclassOf<ARXRockBase> RockClass;

	// 바위에 가할 힘 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RockSetting")
	float ImpulseForce = 2500.f;

	// 발사 방향을 위한 Arrow Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UArrowComponent> ArrowComponent;

};
