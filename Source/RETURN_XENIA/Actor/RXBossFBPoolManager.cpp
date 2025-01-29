// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/RXBossFBPoolManager.h"
#include "RXBossFixedFireball.h"

ARXBossFBPoolManager::ARXBossFBPoolManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARXBossFBPoolManager::BeginPlay()
{
	Super::BeginPlay();

	if (PooledActorClass)
	{
		InitializePool(PooledActorClass, PoolSize);
	}
}

void ARXBossFBPoolManager::InitializePool(TSubclassOf<ARXBossFixedFireball> ActorClass, int32 Size)
{
	if (!ActorClass) return;

	PooledActorClass = ActorClass;
	PoolSize = Size;

	for (int32 i = 0; i < PoolSize; i++)
	{
		ARXBossFixedFireball* NewActor = GetWorld()->SpawnActor<ARXBossFixedFireball>(PooledActorClass);
		if (NewActor)
		{
			NewActor->SetActorHiddenInGame(true);
			NewActor->SetActorEnableCollision(false);
			NewActor->SetActorTickEnabled(false);
			ObjectPool.Add(NewActor);
		}
	}
}

ARXBossFixedFireball* ARXBossFBPoolManager::GetPooledActor()
{
	for (ARXBossFixedFireball* Actor : ObjectPool)
	{
		if (Actor && Actor->IsHidden())  // 사용 가능한 경우 반환
		{
			return Actor;
		}
	}

	// 풀에 남아있는 객체가 없을 경우 새로운 액터 생성
	ARXBossFixedFireball* NewActor = GetWorld()->SpawnActor<ARXBossFixedFireball>(PooledActorClass);
	if (NewActor)
	{
		ObjectPool.Add(NewActor);
	}
	return NewActor;
}

void ARXBossFBPoolManager::FireInCircle(FVector Center, float ZHeight)
{
	int32 NumProjectiles = 40;
	float AngleStep = 360.0f / NumProjectiles;

	// Z축 높이 설정
	Center.Z = ZHeight;

	for (int32 i = 0; i < NumProjectiles; i++)
	{
		float Angle = FMath::DegreesToRadians(i * AngleStep);
		FVector Direction = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);

		ARXBossFixedFireball* Fireball = GetPooledActor();
		if (Fireball)
		{
			Fireball->SetActorLocation(Center);
			Fireball->LaunchProjectile(Direction);
		}
	}
}
// Z = 190에서 발사
void ARXBossFBPoolManager::FireInCircleAt190(FVector Center)
{
	FireInCircle(Center, 190.0f);
}

// Z = 300에서 발사
void ARXBossFBPoolManager::FireInCircleAt300(FVector Center)
{
	FireInCircle(Center, 300.0f);
}