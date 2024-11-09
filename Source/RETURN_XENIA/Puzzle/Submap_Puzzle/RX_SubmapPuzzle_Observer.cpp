// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle/Submap_Puzzle/RX_SubmapPuzzle_Observer.h"
#include "RX_SubmapPuzzle_StartPosition.h"
#include "RX_SubmapPuzzle_EndPosition.h"
#include <Kismet/GameplayStatics.h>
#include "RX_SubmapPuzzle_Rule.h"
#include "RX_SubmapPuzzle_Die.h"
#include "RX_SubmapPuzzle_Coin.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h>

ARX_SubmapPuzzle_Observer::ARX_SubmapPuzzle_Observer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// get start position
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARX_SubmapPuzzle_StartPosition::StaticClass(), tempArray);
	startPosition = Cast<ARX_SubmapPuzzle_StartPosition>(tempArray[0]);

	// get end position
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARX_SubmapPuzzle_EndPosition::StaticClass(), tempArray);
	endPosition = Cast<ARX_SubmapPuzzle_EndPosition>(tempArray[0]);

	// get all puzzle blocks
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARX_SubmapPuzzle_Rule::StaticClass(), tempArray);
	for (AActor* i : tempArray)
	{
		puzzleBlocks.Add(Cast<ARX_SubmapPuzzle_Rule>(i));
	}

	// get all death blocks
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARX_SubmapPuzzle_Die::StaticClass(), tempArray);
	for (AActor* i : tempArray)
	{
		dieBlocks.Add(Cast<ARX_SubmapPuzzle_Die>(i));
	}

	// get all coin blocks
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARX_SubmapPuzzle_Coin::StaticClass(), tempArray);
	for (AActor* i : tempArray)
	{
		coinBlocks.Add(Cast<ARX_SubmapPuzzle_Coin>(i));
	}

	// set coin count
	coinCount = coinBlocks.Num();


	// if coin, change end position color -> edit in blueprint, because of material
	if (coinCount > 0)
	{
		//endPosition->block->SetMaterial()
	}

	// get player
	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ARX_SubmapPuzzle_Observer::BeginPlay()
{
	Super::BeginPlay();


}

void ARX_SubmapPuzzle_Observer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// reset all blocks and restart
void ARX_SubmapPuzzle_Observer::WrongPath()
{
	// player position reset
	player->SetActorLocationAndRotation(startPosition->GetActorLocation(), startPosition->GetActorRotation());
	
	// blocks option reset
	for (ARX_SubmapPuzzle_Rule* block : puzzleBlocks)
	{
		block->isAlreadyTriggered = false;
	}

	// death block is already die
	for (ARX_SubmapPuzzle_Die* block : dieBlocks)
	{
		block->isAlreadyTriggered = true;
	}

	// coin block material change in blueprint
	// end position material change in blueprint
	
	// reset triggered coin count
	triggerCoinCount = 0;
}

// if player position at end position
// check puzzle is cleared
void ARX_SubmapPuzzle_Observer::ClearPath()
{
	bool failFlag = false;

	// check player get all coins
	if (triggerCoinCount != coinCount) failFlag = true;

	// check player attached all blocks
	if (failFlag == false)
	{
		for (ARX_SubmapPuzzle_Rule* block : puzzleBlocks)
		{
			if (failFlag) break;
			if (block->isAlreadyTriggered) continue;

			failFlag = true;
		}
	}


	if (failFlag)
		WrongPath();
	else
		for (ARX_SubmapPuzzle_Rule* block : puzzleBlocks) block->Destroy();
}
