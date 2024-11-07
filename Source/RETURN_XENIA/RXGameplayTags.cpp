// Fill out your copyright notice in the Description page of Project Settings.


#include "RXGameplayTags.h"

namespace RXGameplayTags
{
	//Character Move Section Tag
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Look, "Input.Action.Look");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Jump, "Input.Action.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Interact, "Input.Action.Interact");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_EnterKey, "Input.Action.EnterKey");


	//DialogueData Text Tag , NPC Dialogue Data Section
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Papamama, "Dialogue.NPCType.Papamama");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Sister, "Dialogue.NPCType.Sister"); 
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_VillageHead, "Dialogue.NPCType.VillageHead");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_TempleManager, "Dialogue.NPCType.TempleManager");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_YoungWoman, "Dialogue.NPCType.YoungWoman");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_YoungMan, "Dialogue.NPCType.YoungMan");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Girl, "Dialogue.NPCType.Girl");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Boy, "Dialogue.NPCType.Boy");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Nawiniq, "Dialogue.NPCType.Nawiniq");


	// PlayerStart TeleportSystem Tag Section
	// First Floor
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_GameStart, "PlayerStart.1stFloor.GameStart");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_AltarExit, "PlayerStart.1stFloor.AltarExit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_House1Exit, "PlayerStart.1stFloor.House1Exit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_House2Exit, "PlayerStart.1stFloor.House2Exit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_CaveExit, "PlayerStart.1stFloor.CaveExit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_MainMapExit, "PlayerStart.1stFloor.MainMapExit");

	// Second Floor
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_2ndFloor_MainMapStart, "PlayerStart.2ndFloor.MainMapStart");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_2ndFloor_TempleExit, "PlayerStart.2ndFloor.TempleExit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_2ndFloor_CavinExit, "PlayerStart.2ndFloor.CavinExit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_2ndFloor_MainMapExit, "PlayerStart.2ndFloor.MainMapExit");

	// Third Floor
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_3rdFloor_MainMapStart, "PlayerStart.3rdFloor.MainMapStart");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_3rdFloor_TreeInside, "PlayerStart.3rdFloor.TreeInside");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_3rdFloor_HarpyNest, "PlayerStart.3rdFloor.HarpyNest");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_3rdFloor_TreeTop, "PlayerStart.3rdFloor.TreeTop");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_3rdFloor_MainMapExit, "PlayerStart.3rdFloor.MainMapExit");

	// Sub Maps
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_SubMap1Exit, "PlayerStart.1stFloor.SubMap1Exit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_SubMap2Exit, "PlayerStart.1stFloor.SubMap2Exit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_1stFloor_SubMap3Exit, "PlayerStart.1stFloor.SubMap3Exit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_2ndFloor_SubMap4Exit, "PlayerStart.2ndFloor.SubMap4Exit");
	UE_DEFINE_GAMEPLAY_TAG(PlayerStart_2ndFloor_SubMap5Exit, "PlayerStart.2ndFloor.SubMap5Exit");
}