// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Character/RXPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "System/RXGameInstance.h" 
#include "RXDebugHelper.h"
#include "Actor/RXLevelTeleportActor.h"

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

void ARXLevelTeleportActor::TeleportToOtherLevel()
{
    // 게임 인스턴스에 접근하여 DestinationTag를 설정
    if (URXGameInstance* GameInstance = Cast<URXGameInstance>(GetGameInstance()))
    {
        GameInstance->SetDestinationTag(DestinationTag);
    }

    // 레벨 전환
    UGameplayStatics::OpenLevel(this, NextLevelName);
    
}



