// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "NativeGameplayTags.h"

namespace RXGameplayTags {
	// Player Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Look);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Sprint);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Interact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_EnterKey);

	// Player Puzzel Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_PuzzelMove);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_PuzzelReset);

	// Player UI Input Section
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_ESCKey);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_IKey);

	// Player Circular Puzzel UI
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_Exit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_SwitchTab);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_ClockWiseRotate);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_CP_CounterClockWiseRotate);

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


	// TeleportSystem Tag Section
	// 1층 레벨 텔레포트 시스템 태그 정의
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_MainMap_Start); //게임시작 플레이어 스폰지점

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_Altar_Exit);   //알타 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_Altar_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House1_Exit);  //마을 집1 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House1_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House2_Exit); //마을 집2 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_House2_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_Cave_Exit); //동굴 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_Cave_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_Altar_Exit); //알타 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_Altar_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_MainMap_Exit); //1층 매인맵 출구

	// 2층 레벨 텔레포트 시스템 태그 정의
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_MainMap_Start);  //2층 매인맵 시작

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_Temple_Exit);  //신전 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_Temple_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_Cabin_Exit);  //캐빈 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_Cabin_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_MainMap_Exit); //2층 매인맵 출구

	// 3층 레벨 텔레포트 시스템 태그 정의
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MainMap_Start); //3층 매인맵 시작

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_TreeInside_Exit);  //트리 내부 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_TreeInside_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_HarpyNest_Exit);  //하피 둥지 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_HarpyNest_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_TreeTop_Exit);  //트리 탑 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_TreeTop_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_3rdFloor_MainMap_Exit); //3층 매인맵 출구

	// 서브맵 레벨 텔레포트 시스템 태그 정의
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SubMap1_Exit); //1층 서브맵1 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SubMap1_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SubMap2_Exit); //1층 서브맵2 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SubMap2_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SubMap3_Exit); //1층 서브맵3 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_1stFloor_SubMap3_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_SubMap4_Exit); //2층 서브맵4 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_SubMap4_Entrance);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_SubMap5_Exit); //2층 서브맵5 출입구
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Teleport_2ndFloor_SubMap5_Entrance);
}