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

void ARXBossFBPoolManager::FireTowardsPlayer(FVector Center, float ZHeight, AActor* Target)
{
	if (!Target) return;

	Center.Z = ZHeight; // Z 높이 설정

	//FVector ToPlayer = (Target->GetActorLocation() - Center).GetSafeNormal();
	//FRotator BaseRotation = ToPlayer.Rotation(); // 플레이어를 향한 기본 회전

	// XY 평면에서만 방향을 계산하도록 Z를 0으로 만듦
	FVector ToPlayer = Target->GetActorLocation() - Center;
	ToPlayer.Z = 0; // Z 성분 제거
	ToPlayer = ToPlayer.GetSafeNormal(); // 정규화

	FRotator BaseRotation = ToPlayer.Rotation(); // XY 평면에서의 회전값만 사용

	float LeftLimit = -20.0f;  // 좌측 최대 각도
	float RightLimit = 20.0f;  // 우측 최대 각도
	int32 NumProjectiles = 25; // 총 발사 개수
	float AngleStep = (RightLimit - LeftLimit) / (NumProjectiles - 1);

	for (int32 i = 0; i < NumProjectiles; i++)
	{
		float AngleOffset = LeftLimit + (i * AngleStep);
		FRotator RotatedDirection = BaseRotation + FRotator(0.0f, AngleOffset, 0.0f);
		FVector Direction = RotatedDirection.Vector(); // 회전된 벡터

		ARXBossFixedFireball* Fireball = GetPooledActor();
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
	FireTowardsPlayer(Center, 120.0f, Target);
}

// Z = 300에서 플레이어를 향해 발사
void ARXBossFBPoolManager::FireAtPlayerFrom150(FVector Center, AActor* Target)
{
	FireTowardsPlayer(Center, 210.0f, Target); // 수치 임의 변경
}
