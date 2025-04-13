// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Boss/RXBossProjectileSpawner.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ARXBossProjectileSpawner::ARXBossProjectileSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}
void ARXBossProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();

	// 각 종류의 프로젝트타일을 4개씩 풀링하여 생성
	InitializeProjectilePool(RayPool, RayClass);

	InitializeProjectilePool(TargetingFireballPool, TargetingFireballClass);
}


//  프로젝트타일 풀을 초기화
void ARXBossProjectileSpawner::InitializeProjectilePool(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass)
{
	if (!ProjectileClass) return;

	int32 Count = (ProjectileClass == TargetingFireballClass) ? 25 : 15;
	for (int32 i = 0; i < Count; i++)
	{
		if (UWorld* World = GetWorld())
		{
			AActor* Projectile = World->SpawnActor<AActor>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (Projectile)
			{
				Projectile->SetActorHiddenInGame(true);
				Projectile->SetActorEnableCollision(false);
				Projectile->SetActorTickEnabled(false);
				Pool.Add(Projectile);
			}
		}
	}
}

//  풀에서 프로젝트타일 가져오기 (없으면 새로 생성)
AActor* ARXBossProjectileSpawner::GetProjectileFromPool(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass)
{
	for (AActor* Projectile : Pool)
	{
		if (IsValid(Projectile) && Projectile->IsHidden())
		{
			return Projectile;
		}
	}

	if (UWorld* World = GetWorld())
	{
		AActor* NewProjectile = World->SpawnActor<AActor>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (NewProjectile)
		{
			Pool.Add(NewProjectile);
			return NewProjectile;
		}
	}
	return nullptr;
}

//  프로젝트타일을 풀로 반환
void ARXBossProjectileSpawner::ReturnProjectileToPool(AActor* Projectile, TArray<AActor*>& Pool)
{
	if (IsValid(Projectile) && !Projectile->IsHidden())
	{
		Projectile->SetActorHiddenInGame(true);
		Projectile->SetActorEnableCollision(false);
		Projectile->SetActorTickEnabled(false);
	}
}
void ARXBossProjectileSpawner::FireProjectile(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass, FVector SpawnLocation)
{
	AActor* Projectile = GetProjectileFromPool(Pool, ProjectileClass);
	if (!IsValid(Projectile)) return;

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!IsValid(PlayerCharacter)) return;

	FVector Direction = PlayerCharacter->GetActorLocation() - SpawnLocation;
	Direction.Z = 0.0f;
	Direction.Normalize();

	FRotator LookAtRotation = Direction.Rotation();
	LookAtRotation.Pitch = 0.0f;

	Projectile->SetActorLocation(SpawnLocation);
	Projectile->SetActorRotation(LookAtRotation);
	Projectile->SetActorHiddenInGame(false);
	Projectile->SetActorEnableCollision(true);

	if (UProjectileMovementComponent* ProjectileMovement = Projectile->FindComponentByClass<UProjectileMovementComponent>())
	{
		ProjectileMovement->Velocity = LookAtRotation.Vector() * ProjectileMovement->InitialSpeed;
	}

	TWeakObjectPtr<AActor> WeakProjectile = Projectile;
	TWeakObjectPtr<ARXBossProjectileSpawner> WeakThis = this;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis, WeakProjectile]() {
		if (WeakThis.IsValid() && WeakProjectile.IsValid())
		{
			ARXBossProjectileSpawner* Owner = WeakThis.Get();
			if (!Owner) return;

			if (Owner->RayPool.Contains(WeakProjectile.Get()))
			{
				Owner->ReturnProjectileToPool(WeakProjectile.Get(), Owner->RayPool);
			}
			else if (Owner->TargetingFireballPool.Contains(WeakProjectile.Get()))
			{
				Owner->ReturnProjectileToPool(WeakProjectile.Get(), Owner->TargetingFireballPool);
			}
		}
		}), 6.0f, false);
}