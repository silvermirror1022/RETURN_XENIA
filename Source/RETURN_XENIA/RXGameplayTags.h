// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "NativeGameplayTags.h"

namespace RXGameplayTags {
	// Player Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Look);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Sprint);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Crouch);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Interact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_EnterKey);

	// Player Puzzel Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_PuzzelMove);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_PuzzelReset);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_PuzzelTab);

	// Player KnotHang Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_KnotHang_Hang);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_KnotHang_Exit);

	// Player UI Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_ESCKey);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_IKey);

	// Player Circular Puzzel UI
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_SwitchTab);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_ClockWiseRotate);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_CounterClockWiseRotate);

	// NPC Dialogue Data Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_ClosedDoor);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Sign);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Pachamama_Temple);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Pachamama);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_SubmapBarrier);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Kaira);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Kaira_AfterEvent);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Kaira_Top);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Kaira_TopBoss);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Amarka);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Amarka_AfterEvent);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Amarka_AfterDisaster);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Amarka_AfterDisasterAndEvent);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Winik);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Winik_AfterDisaster);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Solka);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Solka_AfterDisaster);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Dokan);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Dokan_AfterDisaster);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Miru);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Miru_AfterDisaster);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Antuq);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Antuq_AfterEvent);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Nawiniq_Submap1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Nawiniq_Submap2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Nawiniq_Submap3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Nawiniq_Submap4);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Nawiniq_Submap5);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Boss);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(DialogueData_NPC_Boss_Dead);

	// TeleportSystem Tag Section
	// 1층 레벨 텔레포트 시스템 태그 정의
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_MainMap_Start); //게임시작 플레이어 스폰지점

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SolarAltar_Exit);   //알타 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SolarAltar_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House1_Exit);  //마을 집1 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House1_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House2_Exit); //마을 집2 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House2_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_LunarCave_Exit); //동굴 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_LunarCave_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_KinIcestorage_Exit); // 킨의 얼음창고 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_KinIcestorage_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_KabCave_Exit); // 카바의 동굴 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_KabCave_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_NoinikSecretarea_Exit); // 노이닉의 비밀쉼터 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_NoinikSecretarea_Entrance);


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_MainMap_Exit); //1층 매인맵 출구

	// 2층 레벨 텔레포트 시스템 태그 정의
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_MainMap_Start);  //2층 매인맵 시작

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_AbandonedTemple_Exit);  //버려진 신전 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_AbandonedTemple_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_OldManCabin_Exit);  // 노인 오두막 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_OldManCabin_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_AncientVillage_Exit);  // 고대의마을 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_AncientVillage_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_TempleofPachamama_Exit);  // 파차마마의 신전 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_TempleofPachamama_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_MainMap_Exit); //2층 매인맵 출구

	// 3층 레벨 텔레포트 시스템 태그 정의
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MainMap_Start); //3층 매인맵 시작

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MotherNatureTree_Exit);  //대지의 나무 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MotherNatureTree_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MotherNatureEssence_Exit);  //대지의 정수 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MotherNatureEssence_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MainMap_Exit); //3층 매인맵 출구

	
}