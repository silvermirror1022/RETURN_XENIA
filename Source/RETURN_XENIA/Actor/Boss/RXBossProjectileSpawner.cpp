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

	if(ProjectileClass == TargetingFireballClass)
	{
		for (int i = 0; i < 25; i++)
		{
			AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (Projectile)
			{
				Projectile->SetActorHiddenInGame(true);
				Projectile->SetActorEnableCollision(false);
				Pool.Add(Projectile);
			}
		}
	}
	else
	{
		for (int i = 0; i < 15; i++)
		{
			AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (Projectile)
			{
				Projectile->SetActorHiddenInGame(true);
				Projectile->SetActorEnableCollision(false);
				Pool.Add(Projectile);
			}
		}
	}
}

//  풀에서 프로젝트타일 가져오기 (없으면 새로 생성)
AActor* ARXBossProjectileSpawner::GetProjectileFromPool(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass)
{
	// 비활성화된 프로젝트타일 찾기
	for (AActor* Projectile : Pool)
	{
		if (Projectile->IsHidden()) // 비활성화 상태
		{
			return Projectile;
		}
	}

	// 없으면 새로 생성 후 추가
	AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (NewProjectile)
	{
		Pool.Add(NewProjectile);
	}
	return NewProjectile;
}

//  프로젝트타일을 풀로 반환
void ARXBossProjectileSpawner::ReturnProjectileToPool(AActor* Projectile, TArray<AActor*>& Pool)
{
	if (Projectile && !Projectile->IsHidden())
	{
		Projectile->SetActorHiddenInGame(true);
		Projectile->SetActorEnableCollision(false);
		Projectile->SetActorTickEnabled(false);
	}
}
void ARXBossProjectileSpawner::FireProjectile(TArray<AActor*>& Pool, TSubclassOf<AActor> ProjectileClass, FVector SpawnLocation)
{
	AActor* Projectile = GetProjectileFromPool(Pool, ProjectileClass);
	if (Projectile)
	{
		//  플레이어 찾기
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!PlayerCharacter) return;

		FVector PlayerLocation = PlayerCharacter->GetActorLocation();

		// FRotator LookAtRotation = (PlayerLocation - SpawnLocation).Rotation();

		// 플레이어를 바라보는 방향 계산 (XY 평면에서만)
		FVector Direction = (PlayerLocation - SpawnLocation).GetSafeNormal();
		Direction.Z = 0.0f; // Z축 변화를 없애기 위해 고정

		FRotator LookAtRotation = Direction.Rotation(); // Z축을 고려하지 않은 회전
		LookAtRotation.Pitch = 0.0f; // Z축 기울기 제거
		//  프로젝타일 활성화 및 방향 설정
		Projectile->SetActorLocation(SpawnLocation);
		Projectile->SetActorRotation(LookAtRotation);
		Projectile->SetActorHiddenInGame(false);
		Projectile->SetActorEnableCollision(true);

		//  프로젝타일이 이동할 방향 설정 ProjectileMovementComponent 
		UProjectileMovementComponent* ProjectileMovement = Projectile->FindComponentByClass<UProjectileMovementComponent>();
		if (ProjectileMovement)
		{
			ProjectileMovement->Velocity = LookAtRotation.Vector() * ProjectileMovement->InitialSpeed;
		}

		//  일정 시간 후 회수
		if (GetWorld())
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, Projectile, &Pool]() {
				ReturnProjectileToPool(Projectile, Pool);
				}), 6.0f, false);
		}
	}
}