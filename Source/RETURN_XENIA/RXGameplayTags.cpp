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
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_ESCKey, "Input.Action.ESCKey");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_TabKey, "Input.Action.TabKey");


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


	// Teleport Teleport System Section 
	// First Floor
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_MainMap_Start, "Teleport.1stFloor.MainMap.Start");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_Altar_Exit, "Teleport.1stFloor.Altar.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_Altar_Entrance, "Teleport.1stFloor.Altar.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House1_Exit, "Teleport.1stFloor.House1.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House1_Entrance, "Teleport.1stFloor.House1.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House2_Exit, "Teleport.1stFloor.House2.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House2_Entrance, "Teleport.1stFloor.House2.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_Cave_Exit, "Teleport.1stFloor.Cave.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_Cave_Entrance, "Teleport.1stFloor.Cave.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_MainMap_Exit, "Teleport.1stFloor.MainMap.Exit");

	// Second Floor
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_MainMap_Start, "Teleport.2ndFloor.MainMap.Start");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_Temple_Exit, "Teleport.2ndFloor.Temple.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_Temple_Entrance, "Teleport.2ndFloor.Temple.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_Cavin_Exit, "Teleport.2ndFloor.Cavin.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_Cavin_Entrance, "Teleport.2ndFloor.Cavin.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_MainMap_Exit, "Teleport.2ndFloor.MainMap.Exit");

	// Third Floor
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MainMap_Start, "Teleport.3rdFloor.MainMap.Start");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_TreeInside_Exit, "Teleport.3rdFloor.TreeInside.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_TreeInside_Entrance, "Teleport.3rdFloor.TreeInside.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_HarpyNest_Exit, "Teleport.3rdFloor.HarpyNest.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_HarpyNest_Entrance, "Teleport.3rdFloor.HarpyNest.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_TreeTop_Exit, "Teleport.3rdFloor.TreeTop.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_TreeTop_Entrance, "Teleport.3rdFloor.TreeTop.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MainMap_Exit, "Teleport.3rdFloor.MainMap.Exit");

	// Sub Maps
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SubMap1_Exit, "Teleport.1stFloor.SubMap1.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SubMap1_Entrance, "Teleport.1stFloor.SubMap1.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SubMap2_Exit, "Teleport.1stFloor.SubMap2.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SubMap2_Entrance, "Teleport.1stFloor.SubMap2.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SubMap3_Exit, "Teleport.1stFloor.SubMap3.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SubMap3_Entrance, "Teleport.1stFloor.SubMap3.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_SubMap4_Exit, "Teleport.2ndFloor.SubMap4.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_SubMap4_Entrance, "Teleport.2ndFloor.SubMap4.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_SubMap5_Exit, "Teleport.2ndFloor.SubMap5.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_SubMap5_Entrance, "Teleport.2ndFloor.SubMap5.Entrance");
}