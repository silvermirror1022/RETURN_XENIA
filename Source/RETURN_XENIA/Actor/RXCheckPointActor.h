// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RXCheckPointActor.generated.h"

UCLASS()
class RETURN_XENIA_API ARXCheckPointActor : public AActor
{
	GENERATED_BODY()
	/*
	 *	이 엑터는 플레이어가 사망할 시 같은 레벨에서 플레이어를 초기화해서 리스폰 하는 액터임.
	 *	닿을 때마다 그 마지막 체크포인트가 게임인스턴스에 저장됨.
	 *
	 *	주의 : 레벨 간 이동시 초기화될수가 있기 때문에 꼭 레벨 텔레포트하는 출입구에 이 엑터를 모두 배치해야함.
	 */
public:	
	ARXCheckPointActor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelName")
	FName ThisActorLevelName;

protected:
	virtual void BeginPlay() override;

	// 플레이어가 영역에 들어왔을 때 감지할 콜리전 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UBoxComponent> CollisionBox;

	// 오버랩 시작 시 호출될 함수
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);


};
