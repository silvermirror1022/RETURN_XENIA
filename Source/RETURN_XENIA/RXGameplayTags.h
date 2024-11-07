// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "NativeGameplayTags.h"

namespace RXGameplayTags {
	// Player Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Look);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Interact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_EnterKey);


	// NPC Dialogue Data Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Papamama); 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Sister);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_VillageHead); 
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_TempleManager);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_YoungWoman);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_YoungMan);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Girl);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Boy);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Nawiniq);


	// PlayerStart TeleportSystem Tag Section
	// first Floor
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_GameStart);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_AltarExit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_House1Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_House2Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_CaveExit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_MainMapExit);
	// second Floor
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_2ndFloor_MainMapStart);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_2ndFloor_TempleExit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_2ndFloor_CavinExit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_2ndFloor_MainMapExit);
	// third Floor
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_3rdFloor_MainMapStart);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_3rdFloor_TreeInside);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_3rdFloor_HarpyNest);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_3rdFloor_TreeTop);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_3rdFloor_MainMapExit);
	// SUBMAP
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_SubMap1Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_SubMap2Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_1stFloor_SubMap3Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_2ndFloor_SubMap4Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerStart_2ndFloor_SubMap5Exit);
}