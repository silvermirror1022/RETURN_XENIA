// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Boss/RXBossFixedFireball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"

ARXBossFixedFireball::ARXBossFixedFireball()
{
    PrimaryActorTick.bCanEverTick = false;
	Speed = 1500.0f;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
    ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void ARXBossFixedFireball::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(InitialLocation);
}

void ARXBossFixedFireball::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 혹시라도 남아있을 수 있는 타이머 정리
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DeactivationTimer);
	}
}

void ARXBossFixedFireball::LaunchProjectile(FVector Direction)
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	ProjectileMovement->Velocity = Direction * Speed;

	// 6초 후 초기 위치로 리셋
	//GetWorldTimerManager().SetTimer(DeactivationTimer, this, &ARXBossFixedFireball::ResetFireball, 6.0f, false);
	TWeakObjectPtr<ARXBossFixedFireball> WeakThis = this;

	GetWorldTimerManager().SetTimer(DeactivationTimer, FTimerDelegate::CreateLambda([WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->ResetFireball();
			}
		}), 6.0f, false);
}

void ARXBossFixedFireball::ResetFireball()
{
	// 속도 초기화
	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->Velocity = FVector::ZeroVector;

	// 비활성화
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	// 초기 위치로 이동
	SetActorLocation(InitialLocation);

	// 타이머 해제
	GetWorldTimerManager().ClearTimer(DeactivationTimer);
}




