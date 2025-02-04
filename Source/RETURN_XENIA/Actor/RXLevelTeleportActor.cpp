// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/RXLevelTeleportActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/RXGameInstance.h"
#include "RXDebugHelper.h"

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
    // 게임 인스턴스에 접근하여 DestinationTag를 설정
    if (URXGameInstance* GameInstance = Cast<URXGameInstance>(GetGameInstance()))
    {
        GameInstance->SetDestinationTag(DestinationTag);
    }

    // 플레이어 컨트롤러 가져와서 입력 비활성화
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        PlayerController->SetIgnoreMoveInput(true);  // 이동 입력 막기
        //PlayerController->SetIgnoreLookInput(true);  // 카메라 회전 입력 막기
    }

    // 동기 레벨 전환
    // UGameplayStatics::OpenLevel(this, NextLevelName);

    if (NextLevelName.IsNone())
    {
        // 태그가 설정되지 않는 상황 예외처리
        UE_LOG(LogTemp, Warning, TEXT("NextLevelName is not set!"));
        return;
    }

    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.ExecutionFunction = FName("OnLevelLoaded");
    LatentInfo.Linkage = 0;
    LatentInfo.UUID = __LINE__;

    UGameplayStatics::LoadStreamLevel(this, NextLevelName, true, false, LatentInfo);
}

void ARXLevelTeleportActor::OnLevelLoaded() const
{
    UE_LOG(LogTemp, Log, TEXT("Level %s Loaded Successfully"), *NextLevelName.ToString());
    UGameplayStatics::UnloadStreamLevel(this, *GetWorld()->GetMapName(), FLatentActionInfo(), false);
}



