// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle/RollingPuzzle/RX_RollingPuzzle.h"

// Sets default values
ARX_RollingPuzzle::ARX_RollingPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARX_RollingPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARX_RollingPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

