// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RXHarpy.h"
#include "GameFramework/CharacterMovementComponent.h"

ARXHarpy::ARXHarpy()
{
    GetCharacterMovement()->SetMovementMode(MOVE_Flying); // 비행 모드 활성화
}

void ARXHarpy::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->SetMovementMode(MOVE_Flying);

    // 시야 설정 등 AI Perception Component 초기화
    // 플레이어 탐지 시 OnPlayerDetected 이벤트 연결
}
