// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXRockBase.h"
#include "Character/RXPlayer.h"
#include "Player/RXPlayerStatComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

ARXRockBase::ARXRockBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsSmallRock = false;

	// UStaticMeshComponent를 루트 컴포넌트로 설정
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;  // StaticMeshComponent를 루트로 설정

	StaticMeshComponent->SetSimulatePhysics(false);

	// UArrowComponent 생성 후 StaticMeshComponent에 부착
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(StaticMeshComponent);  // StaticMeshComponent를 부모로 설정
	ArrowComponent->ArrowSize = 5.f;
}
void ARXRockBase::BeginPlay()
{
	Super::BeginPlay();

	// 월드 내에서 태그가 "ImpulseSource"인 액터를 찾기
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ImpulseSource"), FoundActors);

	if (FoundActors.Num() > 0)
	{
		// 첫 번째로 찾은 액터를 ImpulseDirActor로 설정
		ImpulseDirActor = FoundActors[0];
	}
}
void ARXRockBase::NotifyHit(
	UPrimitiveComponent* MyComp,
	AActor* Other,
	UPrimitiveComponent* OtherComp,
	bool bSelfMoved,
	FVector HitLocation,
	FVector HitNormal,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// 플레이어인지 확인
	ARXPlayer* Player = Cast<ARXPlayer>(Other);
	if (Player)
	{
		if(URXPlayerStatComponent* PlayerStat = Player->FindComponentByClass<URXPlayerStatComponent>())
		{
			if (bIsSmallRock) return;
			PlayerStat->ApplyDamage(1); // 데미지 적용
		}

		FVector ThisActorLocation = GetActorLocation(); // this 엑터 로케이션
		FVector ImpulseSourceLocation = ImpulseDirActor->GetActorLocation(); // 밀어낼려는방향의 엑터

		FVector ImpulseDirection = (ImpulseSourceLocation - ThisActorLocation).GetSafeNormal(); // 충돌방향벡터

		// 플레이어 밀어내기 -> 캐릭터 무브먼트 
		UCharacterMovementComponent* PlayerMovement = Player->FindComponentByClass<UCharacterMovementComponent>();
		if (PlayerMovement)
		{
			FVector LaunchVelocity = ImpulseDirection * ImpulseForce;
			PlayerMovement->Launch(LaunchVelocity);
		}
	}
}
