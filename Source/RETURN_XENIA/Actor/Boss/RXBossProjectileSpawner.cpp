// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/Boss/RXBossProjectileSpawner.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"

ARXBossProjectileSpawner::ARXBossProjectileSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARXBossProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();

	InitializeProjectilePool(RayPool, RayClass);
	InitializeProjectilePool(TargetingFireballPool, TargetingFireballClass);
}

void ARXBossProjectileSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 레벨 언로드 시 모든 타이머 정리
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
}

void ARXBossProjectileSpawner::InitializeProjectilePool(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass)
{
	if (!ProjectileClass) return;

	const int32 Count = (ProjectileClass == TargetingFireballClass) ? 25 : 15;

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

	if (UWorld* World = GetWorld())
	{
		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis, WeakProjectile]() {
			if (WeakThis.IsValid() && WeakProjectile.IsValid())
			{
				ARXBossProjectileSpawner* Owner = WeakThis.Get();
				if (!Owner) return;

				AActor* ActualProjectile = WeakProjectile.Get();
				if (!ActualProjectile) return;

				if (Owner->RayPool.Contains(ActualProjectile))
				{
					Owner->ReturnProjectileToPool(ActualProjectile, Owner->RayPool);
				}
				else if (Owner->TargetingFireballPool.Contains(ActualProjectile))
				{
					Owner->ReturnProjectileToPool(ActualProjectile, Owner->TargetingFireballPool);
				}
			}
			}), 6.0f, false);
	}
}