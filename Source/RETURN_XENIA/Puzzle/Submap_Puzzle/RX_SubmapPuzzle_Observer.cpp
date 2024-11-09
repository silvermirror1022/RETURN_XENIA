// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle/Submap_Puzzle/RX_SubmapPuzzle_Observer.h"

ARX_SubmapPuzzle_Observer::ARX_SubmapPuzzle_Observer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ARX_SubmapPuzzle_Observer::BeginPlay()
{
	Super::BeginPlay();
}

void ARX_SubmapPuzzle_Observer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARX_SubmapPuzzle_Observer::WrongPath()
{

}
