// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXCircularPuzzelBase.h"
#include "Player/RXPlayerController.h"
#include "Character/RXPlayer.h"
#include "RXDebugHelper.h"
#include "Engine/Engine.h"
#include "Camera/CameraActor.h"

ARXCircularPuzzelBase::ARXCircularPuzzelBase()
{
    PrimaryActorTick.bCanEverTick = false;

    isRotating = false;

    // 초기화
    TargetScore = 0;
    OuterWheel = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    MiddleWheel = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    InnerWheel = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    CurrentSelectedWheel = 0; // 외경 원판 선택
    OuterIndex = 0;
    MiddleIndex = 0;
    InnerIndex = 0;
}

void ARXCircularPuzzelBase::BeginPlay()
{
	Super::BeginPlay();

    Player = Cast<ARXPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
    PlayerController = Cast<ARXPlayerController>(Player->GetController());
}

int32 ARXCircularPuzzelBase::CalculateScore() const
{
    // 각 원판의 현재 선택된 숫자 값을 가정치와 함께 합산
    int32 Score = 0;
    Score += OuterWheel[OuterIndex] * 100; // 외경 원판
    Score += MiddleWheel[MiddleIndex] * 10; // 중간 원판
    Score += InnerWheel[InnerIndex] * 1; // 안쪽 원판
    return Score;
}

bool ARXCircularPuzzelBase::IsCorrectAnswer() const
{
    // 현재 점수가 정당인지 확인
    return CalculateScore() == TargetScore;
}

void ARXCircularPuzzelBase::PuzzelEventStart_Implementation()
{
	Super::PuzzelEventStart_Implementation();
    // 퍼즐 모드 카메라로 전환, 변수 활성화
    SwitchToCamera(PuzzelModeCamera, 0.0f);
    if (PuzzelModeCamera && Player)
    {
        // 플래이어를 현재 통장 컨트롤 가격에 지원하는 위치로 이동
        FVector CameraBackLocation = PuzzelModeCamera->GetActorLocation() - PuzzelModeCamera->GetActorForwardVector() * 200.0f;
        CameraBackLocation.Z = PuzzelModeCamera->GetActorLocation().Z;

        Player->SetActorLocation(CameraBackLocation);
        PlayerController->SetViewTargetWithBlend(PuzzelModeCamera, 0.0f);
    }
    Player->bIsCircularPuzzelMode = true;
}

void ARXCircularPuzzelBase::PuzzelEventFinish_Implementation()
{
	Super::PuzzelEventFinish_Implementation();
    // 원래 플레이어 카메리로 복귀, 변수 복구
    SwitchToCamera(Player, 0.0f);
    Player->bIsCircularPuzzelMode = false;
}

void ARXCircularPuzzelBase::RotateToClockWise_Implementation()
{
    if (isRotating) return;

    switch (CurrentSelectedWheel)
    {
    case 0: // 외경 원판
        RotateWheel(OuterIndex, OuterWheel, true);
        D(FString::Printf(TEXT("Outer Wheel rotated clockwise to index: %d"), OuterIndex));
        break;
    case 1: // 중간 원판
        RotateWheel(MiddleIndex, MiddleWheel, true);
        D(FString::Printf(TEXT("Middle Wheel rotated clockwise to index: %d"), MiddleIndex));
        break;
    case 2: // 안쪽 원판
        RotateWheel(InnerIndex, InnerWheel, true);
        D(FString::Printf(TEXT("Inner Wheel rotated clockwise to index: %d"), InnerIndex));
        break;
    default:
        break;
    }
}

void ARXCircularPuzzelBase::RotateToCounterClockWise_Implementation()
{
    if (isRotating) return;

    switch (CurrentSelectedWheel)
    {
    case 0: // 외경 원판
        RotateWheel(OuterIndex, OuterWheel, false);
        D(FString::Printf(TEXT("Outer Wheel rotated counter-clockwise to index: %d"), OuterIndex));
        break;
    case 1: // 중간 원판
        RotateWheel(MiddleIndex, MiddleWheel, false);
        D(FString::Printf(TEXT("Middle Wheel rotated counter-clockwise to index: %d"), MiddleIndex));
        break;
    case 2: // 안쪽 원판
        RotateWheel(InnerIndex, InnerWheel, false);
        D(FString::Printf(TEXT("Inner Wheel rotated counter-clockwise to index: %d"), InnerIndex));
        break;
    default:
        break;
    }
}

void ARXCircularPuzzelBase::SwitchSelectedWheel_Implementation()
{
    CurrentSelectedWheel = (CurrentSelectedWheel + 1) % 3;
    switch (CurrentSelectedWheel)
    {
    case 0:
        D("Switched to Outer Wheel.");
        break;
    case 1:
        D("Switched to Middle Wheel.");
        break;
    case 2:
        D("Switched to Inner Wheel.");
        break;
    default:
        break;
    }
}

void ARXCircularPuzzelBase::RotateWheel(int32& CurrentIndex, const TArray<int32>& Wheel, bool bClockwise)
{
    // 현재 인덱스를 시계/반시계 반환
    int32 MaxIndex = Wheel.Num();
    if (bClockwise)
    {
        CurrentIndex = (CurrentIndex + 1) % MaxIndex;
    }
    else
    {
        CurrentIndex = (CurrentIndex - 1 + MaxIndex) % MaxIndex;
    }
}

void ARXCircularPuzzelBase::SwitchToCamera(AActor* NewCamera, float BlendTime) const
{
    if (PlayerController && NewCamera)
    {
        PlayerController->SetViewTargetWithBlend(NewCamera, BlendTime);
    }
}
