// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/RXLevelTeleportActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/RXGameInstance.h"
#include "RXDebugHelper.h"
#include "Data/RXAssetData.h"
#include "System/RXAssetManager.h"

ARXLevelTeleportActor::ARXLevelTeleportActor()
{

    // Sphere Component CDO 생성 및 설정
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(RootComponent);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


    // Sphere Component의 반지름과 색상 설정
    SphereComponent->SetSphereRadius(80.0f); // 반지름 설정
    SphereComponent->ShapeColor = FColor::Green; // 색상 설정 (디버그용)

}

void ARXLevelTeleportActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARXLevelTeleportActor::TeleportToOtherLevel_Implementation()
{
    if (NextLevelName.IsNone())
    {
        UE_LOG(LogTemp, Warning, TEXT("NextLevelName is not set!"));
        return;
    }

    // 게임 인스턴스에 DestinationTag 설정
    if (URXGameInstance* GameInstance = Cast<URXGameInstance>(GetGameInstance()))
    {
        GameInstance->SetDestinationTag(DestinationTag);
        GameInstance->CurrentLevelName = NextLevelName;
    }


	// 자산 로드 완료 후 레벨 전환
	//UGameplayStatics::OpenLevel(this, NextLevelName);

}



