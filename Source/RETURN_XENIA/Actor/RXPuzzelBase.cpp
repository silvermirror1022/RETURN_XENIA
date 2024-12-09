// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXPuzzelBase.h"

#include "Component/RXPuzzelStartComponent.h"

ARXPuzzelBase::ARXPuzzelBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;

}

void ARXPuzzelBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARXPuzzelBase::PuzzelEventStart()
{
	if(URXPuzzelStartComponent* PuzzelStartComponent = FindComponentByClass<URXPuzzelStartComponent>())
	{
		PuzzelStartComponent->StartPuzzelMode();
	}
}


