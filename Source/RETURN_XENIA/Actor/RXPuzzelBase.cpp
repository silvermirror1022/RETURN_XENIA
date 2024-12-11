// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXPuzzelBase.h"
#include "Component/RXPuzzelEventManageComponent.h"
#include "Component/RXPuzzelSpawnManageComponent.h"
ARXPuzzelBase::ARXPuzzelBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	//RootComponent = CreateDefaultSubobject<URXPuzzelSpawnManageComponent>(TEXT("SpawnManageComponent"));
}

void ARXPuzzelBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARXPuzzelBase::PuzzelEventStart()
{
	if(URXPuzzelEventManageComponent* PuzzelEventManageComponent = FindComponentByClass<URXPuzzelEventManageComponent>())
	{
		PuzzelEventManageComponent->StartPuzzelMode();
	}
}


