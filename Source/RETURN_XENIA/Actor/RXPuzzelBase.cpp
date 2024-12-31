// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXPuzzelBase.h"
#include "Component/RXPuzzelEventManageComponent.h"
#include "Component/RXPuzzelSpawnManageComponent.h"

ARXPuzzelBase::ARXPuzzelBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARXPuzzelBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARXPuzzelBase::PuzzelEventStart_Implementation()
{
	if (URXPuzzelEventManageComponent* PuzzelEventManageComponent = FindComponentByClass<URXPuzzelEventManageComponent>())
	{
		PuzzelEventManageComponent->StartPuzzelMode();
	}
	//if (URXPuzzelSpawnManageComponent* PuzzelSpawnManageComponent = FindComponentByClass<URXPuzzelSpawnManageComponent>())
	//{
	//	PuzzelSpawnManageComponent->ActivateLevel(1);
	//}
}

/*
 * 실제 퍼즐이벤트 시작 종료는 퍼즐이벤트매니지컴포넌트에서 관리중임.
 * 해당 부모 퍼즐의 PuzzelEventStart는 컴포넌트의 실행 역할만 함,
 * PuzzelEventFinish함수는 해당 Base가 가진 자식 컴포넌트 매시, 인터렉션비지빌리티등을 쉽게 제거하기 위해
 * 블루프린트에서 진행하기 위해서 BlueprintNativeEvent로 혼합,
 * 실제로 컴포넌트에서도 퍼즐종료함수를 부르고 이 함수를 불러줘야 끝나게 됨.
 * 블루프린트 퍼즐이벤트메니지컴포넌트의 마지막 부분 흐름에서 호출 중임.
 */

void ARXPuzzelBase::PuzzelEventFinish_Implementation()
{
	// All Clear Child Component When Player Clear PuzzelEvent (Implementation in Blueprint)

	
}


