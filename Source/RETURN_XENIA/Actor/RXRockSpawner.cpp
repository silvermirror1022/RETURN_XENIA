// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXRockSpawner.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"

ARXRockSpawner::ARXRockSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	// 루트 컴포넌트 설정
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// 방향을 설정할 ArrowComponent 생성
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	ArrowComponent->ArrowSize = 5.f;
}

void ARXRockSpawner::BeginPlay()
{
	Super::BeginPlay();
	// 초기 Rock Pool 세팅
	for (int32 i = 0; i < MaxRockCount; i++)
	{
		AActor* NewRock = GetWorld()->SpawnActor<AActor>(RockClass, ArrowComponent->GetComponentLocation(), 
			ArrowComponent->GetComponentRotation());
		if (NewRock)
		{
			NewRock->SetActorHiddenInGame(true);
			NewRock->SetActorEnableCollision(false);
			RockPool.Add(NewRock);
		}
	}
}
// 바위 발사 함수
void ARXRockSpawner::SpawnRock()
{
	if (RockPool.Num() == 0) return;

	// 풀에서 Rock 가져오기
	AActor* Rock = RockPool.Pop();
	if (!Rock) return;

	// Rock을 현재 Spawner 위치로 이동
	Rock->SetActorLocation(ArrowComponent->GetComponentLocation());
	Rock->SetActorRotation(ArrowComponent->GetComponentRotation());
	Rock->SetActorHiddenInGame(false);
	Rock->SetActorEnableCollision(true);

	// 방향 벡터 계산 후 Impulse 적용
	FVector LaunchDirection = ArrowComponent->GetForwardVector();
	UStaticMeshComponent* MeshComp = Rock->FindComponentByClass<UStaticMeshComponent>();
	if (MeshComp)
	{
		MeshComp->SetSimulatePhysics(true);
		MeshComp->AddImpulse(LaunchDirection * ImpulseForce, NAME_None, true);
	}

	// 6초 후 Rock 반환
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ARXRockSpawner::ReturnRockToPool, Rock);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 6.f, false);
}

// 바위를 다시 풀로 반환
void ARXRockSpawner::ReturnRockToPool(AActor* Rock)
{	
	if (!Rock) return;

	// 물리 및 충돌 비활성화
	UStaticMeshComponent* MeshComp = Rock->FindComponentByClass<UStaticMeshComponent>();
	if (MeshComp)
	{
		MeshComp->SetSimulatePhysics(false);  // 물리 시뮬레이션 OFF
	}

	// 물리 비활성화 및 위치 초기화
	Rock->SetActorHiddenInGame(true);
	Rock->SetActorEnableCollision(false);
	Rock->SetActorLocation(ArrowComponent->GetComponentLocation());

	// 풀에 다시 추가
	RockPool.Add(Rock);
}