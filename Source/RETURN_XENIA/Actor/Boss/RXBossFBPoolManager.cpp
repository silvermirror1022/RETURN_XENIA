// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/Boss/RXBossFBPoolManager.h"
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
		InitializePool(PooledActorClass, PooledActorClass2, PoolSize);
	}
}

void ARXBossFBPoolManager::InitializePool(TSubclassOf<ARXBossFixedFireball> ActorClass1, TSubclassOf<ARXBossFixedFireball> ActorClass2, int32 Size)
{
	if (!ActorClass1 || !ActorClass2) return;

	PooledActorClass = ActorClass1;
	PooledActorClass2 = ActorClass2;
	PoolSize = Size;

	// 첫 번째 풀 초기화
	for (int32 i = 0; i < PoolSize / 2; i++)
	{
		ARXBossFixedFireball* NewActor = GetWorld()->SpawnActor<ARXBossFixedFireball>(PooledActorClass);
		if (NewActor)
		{
			NewActor->SetActorHiddenInGame(true);
			NewActor->SetActorEnableCollision(false);
			NewActor->SetActorTickEnabled(false);
			ObjectPool1.Add(NewActor);
		}
	}

	// 두 번째 풀 초기화
	for (int32 i = 0; i < PoolSize / 2; i++)
	{
		ARXBossFixedFireball* NewActor = GetWorld()->SpawnActor<ARXBossFixedFireball>(PooledActorClass2);
		if (NewActor)
		{
			NewActor->SetActorHiddenInGame(true);
			NewActor->SetActorEnableCollision(false);
			NewActor->SetActorTickEnabled(false);
			ObjectPool2.Add(NewActor);
		}
	}
}
ARXBossFixedFireball* ARXBossFBPoolManager::GetPooledActor(bool bUseFirstPool)
{
	TArray<ARXBossFixedFireball*>& SelectedPool = bUseFirstPool ? ObjectPool1 : ObjectPool2;

	for (ARXBossFixedFireball* Actor : SelectedPool)
	{
		if (Actor && Actor->IsHidden())  // 사용 가능한 경우 반환
		{
			return Actor;
		}
	}

	// 풀에 남아있는 객체가 없을 경우 새로운 액터 생성
	TSubclassOf<ARXBossFixedFireball> ActorClass = bUseFirstPool ? PooledActorClass : PooledActorClass2;
	ARXBossFixedFireball* NewActor = GetWorld()->SpawnActor<ARXBossFixedFireball>(ActorClass);
	if (NewActor)
	{
		SelectedPool.Add(NewActor);
	}
	return NewActor;
}

void ARXBossFBPoolManager::FireTowardsPlayer(FVector Center, float ZHeight, AActor* Target, bool bUseFirstPool)
{
	if (!Target) return;

	Center.Z = ZHeight;

	FVector ToPlayer = Target->GetActorLocation() - Center;
	ToPlayer.Z = 0;
	ToPlayer = ToPlayer.GetSafeNormal();

	FRotator BaseRotation = ToPlayer.Rotation();

	float LeftLimit = -20.0f;
	float RightLimit = 20.0f;
	int32 NumProjectiles = 25;
	float AngleStep = (RightLimit - LeftLimit) / (NumProjectiles - 1);

	for (int32 i = 0; i < NumProjectiles; i++)
	{
		float AngleOffset = LeftLimit + (i * AngleStep);
		FRotator RotatedDirection = BaseRotation + FRotator(0.0f, AngleOffset, 0.0f);
		FVector Direction = RotatedDirection.Vector();

		//  120에서는 첫 번째 풀, 150에서는 두 번째 풀에서 가져오기 
		ARXBossFixedFireball* Fireball = GetPooledActor(bUseFirstPool);

		if (Fireball)
		{
			Fireball->SetActorLocation(Center);
			Fireball->LaunchProjectile(Direction);
		}
	}
}

// Z = 190에서 플레이어를 향해 발사
void ARXBossFBPoolManager::FireAtPlayerFrom120(FVector Center, AActor* Target)
{
	FireTowardsPlayer(Center, 120.0f, Target, true);
}

// Z = 300에서 플레이어를 향해 발사
void ARXBossFBPoolManager::FireAtPlayerFrom150(FVector Center, AActor* Target)
{
	FireTowardsPlayer(Center, 190.0f, Target, false);
}
