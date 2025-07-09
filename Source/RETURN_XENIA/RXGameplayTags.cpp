// Fill out your copyright notice in the Description page of Project Settings.


#include "RXGameplayTags.h"

namespace RXGameplayTags
{
	//Player Move Section Tag
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Look, "Input.Action.Look");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Jump, "Input.Action.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Sprint, "Input.Action.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Crouch, "Input.Action.Crouch");

	// except : used for PuzzelInputMappingContext : PuzzelMode Section
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_PuzzelMove, "Input.Action.PuzzelMove");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_PuzzelReset, "Input.Action.PuzzelReset");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_PuzzelTab, "Input.Action.PuzzelTab");

	// except : used for PuzzelInputMappingContext : CircularPuzzelMode Section
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_CP_Exit, "Input.Action.CircularPuzzel.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_CP_SwitchTab, "Input.Action.CircularPuzzel.SwitchTab");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_CP_ClockWiseRotate, "Input.Action.CircularPuzzel.ClockWiseRotate");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_CP_CounterClockWiseRotate, "Input.Action.CircularPuzzel.CounterClockWiseRotate");

	// except : used for KnotHangMappingContext : HangingKnotMode Section
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_KnotHang_Hang, "Input.Action.KnotHang.Hang");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_KnotHang_Exit, "Input.Action.KnotHang.Exit");

	//Player Others Section
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Interact, "Input.Action.Interact");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_TabKey, "Input.Action.TabKey");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_ESCKey, "Input.Action.ESCKey");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_IKey, "Input.Action.IKey");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_MapKey, "Input.Action.MapKey");

	//DialogueData Text Tag , NPC Dialogue Data Section
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_ClosedDoor, "Dialogue.NPCType.ClosedDoor");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_WinikClosedDoor, "Dialogue.NPCType.WinikClosedDoor");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Sign, "Dialogue.NPCType.Sign");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_RockChar, "Dialogue.NPCType.RockChar");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_EasterEgg, "Dialogue.NPCType.EasterEgg");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Pachamama, "Dialogue.NPCType.Pachamama");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Pachamama_Temple, "Dialogue.NPCType.Pachamama.Temple");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Pachamama_InBossBattle, "Dialogue.NPCType.Pachamama.InBossBattle");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_SubmapBarrier, "Dialogue.NPCType.SubmapBarrier");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Kaira, "Dialogue.NPCType.Kaira");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Kaira_AfterEvent, "Dialogue.NPCType.Kaira.AfterEvent");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Kaira_Top, "Dialogue.NPCType.Kaira.Top");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Kaira_TopBoss, "Dialogue.NPCType.Kaira.TopBoss");
	
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Amarka, "Dialogue.NPCType.Amarka");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Amarka_AfterEvent, "Dialogue.NPCType.Amarka.AfterEvent");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Amarka_AfterDisaster, "Dialogue.NPCType.Amarka.AfterDisaster");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Amarka_AfterDisasterAndEvent, "Dialogue.NPCType.Amarka.AfterDisasterAndEvent");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Winik, "Dialogue.NPCType.Winik");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Winik_AfterDisaster, "Dialogue.NPCType.Winik.AfterDisaster");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Solka, "Dialogue.NPCType.Solka");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Solka_AfterDisaster, "Dialogue.NPCType.Solka.AfterDisaster");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Dokan, "Dialogue.NPCType.Dokan");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Dokan_AfterDisaster, "Dialogue.NPCType.Dokan.AfterDisaster");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Miru, "Dialogue.NPCType.Miru");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Miru_AfterDisaster, "Dialogue.NPCType.Miru.AfterDisaster");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Antuq, "Dialogue.NPCType.Antuq");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Antuq_AfterDisaster, "Dialogue.NPCType.Antuq.AfterDisaster");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Nawiniq_Submap1, "Dialogue.NPCType.Nawiniq.Submap1");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Nawiniq_Submap2, "Dialogue.NPCType.Nawiniq.Submap2");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Nawiniq_Submap3, "Dialogue.NPCType.Nawiniq.Submap3");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Nawiniq_Submap4, "Dialogue.NPCType.Nawiniq.Submap4");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Nawiniq_Submap5, "Dialogue.NPCType.Nawiniq.Submap5");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Nawiniq_3Floor, "Dialogue.NPCType.Nawiniq.3Floor");

	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Boss, "Dialogue.NPCType.Boss");
	UE_DEFINE_GAMEPLAY_TAG(DialogueData_NPC_Boss_Dead, "Dialogue.NPCType.Boss.Dead");

	// Teleport System Section 
	// First Floor
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_MainMap_Start, "Teleport.1stFloor.MainMap.Start");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SolarAltar_Exit, "Teleport.1stFloor.SolarAltar.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_SolarAltar_Entrance, "Teleport.1stFloor.SolarAltar.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House1_Exit, "Teleport.1stFloor.House1.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House1_Entrance, "Teleport.1stFloor.House1.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House2_Exit, "Teleport.1stFloor.House2.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_House2_Entrance, "Teleport.1stFloor.House2.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_LunarCave_Exit, "Teleport.1stFloor.LunarCave.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_LunarCave_Entrance, "Teleport.1stFloor.LunarCave.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_KinIcestorage_Exit, "Teleport.1stFloor.KinIcestorage.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_KinIcestorage_Entrance, "Teleport.1stFloor.KinIcestorage.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_KabCave_Exit, "Teleport.1stFloor.KabCave.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_KabCave_Entrance, "Teleport.1stFloor.KabCave.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_NoinikSecretarea_Exit, "Teleport.1stFloor.NoinikSecretarea.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_NoinikSecretarea_Entrance, "Teleport.1stFloor.NoinikSecretarea.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_1stFloor_MainMap_Exit, "Teleport.1stFloor.MainMap.Exit");

	// Second Floor
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_MainMap_Start, "Teleport.2ndFloor.MainMap.Start");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_AbandonedTemple_Exit, "Teleport.2ndFloor.AbandonedTemple.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_AbandonedTemple_Entrance, "Teleport.2ndFloor.AbandonedTemple.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_OldManCabin_Exit, "Teleport.2ndFloor.OldManCabin.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_OldManCabin_Entrance, "Teleport.2ndFloor.OldManCabin.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_AncientVillage_Exit, "Teleport.2ndFloor.AncientVillage.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_AncientVillage_Entrance, "Teleport.2ndFloor.AncientVillage.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_TempleofPachamama_Exit, "Teleport.2ndFloor.TempleofPachamama.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_TempleofPachamama_Entrance, "Teleport.2ndFloor.TempleofPachamama.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_2ndFloor_MainMap_Exit, "Teleport.2ndFloor.MainMap.Exit");

	// Third Floor
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MainMap_Start, "Teleport.3rdFloor.MainMap.Start");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MotherNatureTree_Exit, "Teleport.3rdFloor.MotherNatureTree.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MotherNatureTree_Entrance, "Teleport.3rdFloor.MotherNatureTree.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MotherNatureEssence_Exit, "Teleport.3rdFloor.MotherNatureEssence.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MotherNatureEssence_Entrance, "Teleport.3rdFloor.MotherNatureEssence.Entrance");
	UE_DEFINE_GAMEPLAY_TAG(Teleport_3rdFloor_MainMap_Exit, "Teleport.3rdFloor.MainMap.Exit");
}