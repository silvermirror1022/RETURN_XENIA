// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RXPuzzelBaseObject.h"
#include "RXPuzzelBase.h"
#include "Component/RXPuzzelSpawnManageComponent.h"

ARXPuzzelBaseObject::ARXPuzzelBaseObject()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARXPuzzelBaseObject::BeginPlay()
{
	Super::BeginPlay();
}

void ARXPuzzelBaseObject::ResetObjectState_Implementation()
{
}


