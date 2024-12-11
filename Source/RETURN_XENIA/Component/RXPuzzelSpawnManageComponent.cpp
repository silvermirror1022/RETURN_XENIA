// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RXPuzzelSpawnManageComponent.h"
#include "Actor/RXPuzzelBaseObject.h"
#include "Character/RXPlayer.h"
#include "Kismet/GameplayStatics.h"

URXPuzzelSpawnManageComponent::URXPuzzelSpawnManageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    CurrentLevelID = 1;
}

void URXPuzzelSpawnManageComponent::BeginPlay()
{
	Super::BeginPlay();
    Player = Cast<ARXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	InitializeTileData();
}
void URXPuzzelSpawnManageComponent::InitializeTileData()
{
    if (LevelTag.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No data for LevelTag ID, NEED TO SET!!"));
    }
    /*
     *  각각 해당하는 모든 오브젝트는 태그를 설정해줘야함. 철자는 무조건 동일해야함.
     *  해당 컴포넌트는 블루프린트로 각각 파생해서 해당 퍼즐에 붙여줘야함. 에디터에서 설정.
     *
     *  오일러퍼즐:    EulerPuzzelLevel1, EulerPuzzelLevel2, EulerPuzzelLevel3, EulerPuzzelLevel4
     *  블라인드퍼즐:  BlindPuzzelLevel1, BlindPuzzelLevel2, BlindPuzzelLevel3, BlindPuzzelLevel4
     *  밀기퍼즐:      PushablePuzzelLevel1, PushablePuzzelLevel2, PushablePuzzelLevel3, PushablePuzzelLevel4
     *  패턴퍼즐:      PatternPuzzelLevel1, PatternPuzzelLevel2, PatternPuzzelLevel3, PatternPuzzelLevel4
     *  타이밍퍼즐:    TimingPuzzelLevel1, TimingPuzzelLevel2, TimingPuzzelLevel3, TimingPuzzelLevel4
     */


    for (int32 LevelID = 1; LevelID <= LevelTag.Num(); ++LevelID)
    {
    	// 각각 월드에 배치된 모든 레벨1~4 의 액터들을 순회
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), LevelTag[LevelID - 1], FoundActors);

        TArray<AActor*> ValidActors;
        for (AActor* Actor : FoundActors)
        {
            if (Actor && Actor->IsA<ARXPuzzelBaseObject>())
            {
                ValidActors.Add(Actor);
            }
        }
        // 유효하면 해당 엑터들을 LevelObjectsMap 에 레벨과 매핑하여 Map에 저장
        if (ValidActors.Num() > 0)
        {
            LevelObjectsMap.Add(LevelID, ValidActors);
        }
    }

    // 기본 활성화 레벨 (첫번째 레벨1)
    ActivateLevel(CurrentLevelID);
}
void URXPuzzelSpawnManageComponent::ActivateLevel(int32 LevelID)
{
    CurrentLevelID = LevelID;

    for (auto& Pair : LevelObjectsMap)
    {
        int32 ID = Pair.Key; // 현재 레벨
        TArray<AActor*>& Actors = Pair.Value; // 현재 레벨에 매핑된 오브젝트액터들 배열

        for (AActor* Actor : Actors)
        {
            if (Actor)
            {
                if (ID == LevelID)
                {
                    // 현재 레벨에 해당하는 모든액터들(배열)에 동적 태그 추가, 활성화
                    Actor->Tags.AddUnique(FName("UnderwayPuzzel"));
                    Actor->SetActorHiddenInGame(false);
                    Actor->SetActorEnableCollision(true);
                }
                else
                {
                    // 아닌 것들은 제외, 비활성화
                    Actor->Tags.Remove(FName("UnderwayPuzzel"));
                    Actor->SetActorHiddenInGame(true);
                    Actor->SetActorEnableCollision(false);
                }
            }
        }
    }
}

void URXPuzzelSpawnManageComponent::ResetCurrentLevel_Implementation()
{
    if (!LevelObjectsMap.Contains(CurrentLevelID))
    {
        UE_LOG(LogTemp, Warning, TEXT("No data for Level ID: %d"), CurrentLevelID);
        return;
    }

    // 현재 레벨의 타일 엑터 리셋
    for (AActor* Actor : LevelObjectsMap[CurrentLevelID])
    {
        if (ARXPuzzelBaseObject* PuzzelObject = Cast<ARXPuzzelBaseObject>(Actor))
        {
            PuzzelObject->ResetObjectState(); // 각 오브젝트의 상태 리셋 호출
        }
    }

    // StartPos 태그가 있는 액터를 검색
    TArray<AActor*> TaggedActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PuzzelStartPos"), TaggedActors);

    if (TaggedActors.Num() > 0)
    {
        // 첫 번째 태그 액터의 위치로 이동
        AActor* StartPosActor = TaggedActors[0];
        if (StartPosActor && Player)
        {
            FVector TargetLocation = StartPosActor->GetActorLocation();
            TargetLocation.Z += 40.0f;
            Player->SetActorLocation(TargetLocation);
        }
    }
}