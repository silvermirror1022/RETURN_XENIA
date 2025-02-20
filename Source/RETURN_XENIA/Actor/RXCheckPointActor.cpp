// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXCheckPointActor.h"
#include "Components/BoxComponent.h"
#include "System/RXGameInstance.h"
#include "GameFramework/Actor.h"
#include "Character/RXPlayer.h"
#include "Kismet/GameplayStatics.h"

ARXCheckPointActor::ARXCheckPointActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// CollisionBox 생성 및 기본 설정
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	// 콜리전 설정: Pawn과의 오버랩만 허용
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ARXCheckPointActor::BeginPlay()
{
	Super::BeginPlay();
	// 오버랩 이벤트 바인딩
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARXCheckPointActor::OnOverlapBegin);
	}
}

void ARXCheckPointActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// OtherActor가 유효한지 체크
	if ((OtherActor && OtherActor->IsA<ARXPlayer>()))
	{
		// 게임 인스턴스 가져오기
		if (URXGameInstance* GI = Cast<URXGameInstance>(UGameplayStatics::GetGameInstance(this)))
		{
			// 체크포인트 정보를 저장 
			GI->CheckpointTransform = GetActorTransform();

			//UE_LOG(LogTemp, Log, TEXT("Checkpoint updated at location: %s"), *GetActorLocation().ToString());
		}
	}
}

