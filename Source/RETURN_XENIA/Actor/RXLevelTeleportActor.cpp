// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/RXLevelTeleportActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "System/RXGameInstance.h"
#include "Character/RXPlayer.h"
#include "Player/RXPlayerStatComponent.h"
#include "RXDebugHelper.h"
#include "System/RXAssetManager.h"
#include "Data/RXMapData.h"

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

    // 플레이어 액터 가져와 무적 상태로 (텔포시 데미지 받는 버그 방지용)
    ARXPlayer* Player = Cast<ARXPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (Player)
    {
        // 플레이어의 스탯 컴포넌트 가져오기
        URXPlayerStatComponent* StatComp = Player->FindComponentByClass<URXPlayerStatComponent>();
        if (StatComp)
        {
            // 무적 상태 활성화
            StatComp->bIsImmortal = true;
        }
    }

    // 게임 인스턴스에 DestinationTag 설정
    if (URXGameInstance* GameInstance = Cast<URXGameInstance>(GetGameInstance()))
    {
        GameInstance->SetDestinationTag(DestinationTag);
        GameInstance->CurrentLevelName = NextLevelName;
    }
    // **Data Asset을 사용한 맵 로드**
    LoadLevelUsingMapData();
}

void ARXLevelTeleportActor::LoadLevelUsingMapData()
{
    // **Map Data를 가져오기**
    const URXMapData* MapData = URXAssetManager::GetAssetByName<URXMapData>("MapData");

    if (!MapData)
    {
        UE_LOG(LogTemp, Error, TEXT("MapData is not loaded!"));
        return;
    }

    // **NextLevelName에 해당하는 맵 경로를 찾기**
    const FRXMapDataInfo* MapDataEntry = MapData->FindMapDataByName(NextLevelName);

    if (!MapDataEntry)
    {
        UE_LOG(LogTemp, Error, TEXT("Map [%s] not found in MapData!"), *NextLevelName.ToString());
        return;
    }

    FSoftObjectPath MapPath = MapDataEntry->MapAssetPath;

    if (!MapPath.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Map Path for [%s]!"), *NextLevelName.ToString());
        return;
    }

    // **비동기 로드 시작**
    UE_LOG(LogTemp, Log, TEXT("Starting async load for level: %s"), *MapPath.ToString());

    URXAssetManager::GetStreamableManager().RequestAsyncLoad(
        MapPath,
        FStreamableDelegate::CreateUObject(this, &ARXLevelTeleportActor::OnLevelLoadCompleted, MapPath)
    );
}

void ARXLevelTeleportActor::OnLevelLoadCompleted(FSoftObjectPath LoadedMapPath) const
{
    UE_LOG(LogTemp, Log, TEXT("Level Load Completed! Opening Level: %s"), *LoadedMapPath.ToString());

    // FSoftObjectPath에서 FName으로 변환 후 OpenLevel 호출
    FName LevelName = FName(*LoadedMapPath.GetAssetName());

    if (!LevelName.IsNone())
    {
        UGameplayStatics::OpenLevel(this, LevelName);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to convert SoftObjectPath to LevelName!"));
    }
}