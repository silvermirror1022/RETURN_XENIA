// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RXCharacterBase.h"
#include "GameplayTagContainer.h"
#include "Interface/RXNPCDialogueInterface.h"
#include "RXNonPlayer.generated.h"

class UTextBlock;

UCLASS()
class RETURN_XENIA_API ARXNonPlayer : public ARXCharacterBase, public IRXNPCDialogueInterface
{
	GENERATED_BODY()

public:
	//가까이가면 상호작용 E UI띄우는 로직은 RXInteractionVisibilityComponent를 통해 구현
	ARXNonPlayer();

protected: 
	virtual void BeginPlay() override;

public:
	//RXNPCDialogueInterface Interface Virtual Func override Implementation
	UFUNCTION(BlueprintCallable)
	virtual void StartDialogue() override;
	virtual void DisplayDialogue() override;
	virtual void EndDialogue() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCTypeName")
	FText NPCEng_Name; //NPC 영어 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCTypeName")
	FText NPCKor_Name; // NPC 한국 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCTypeTag")
	FGameplayTag NPCType; //NPC마다 가지고있는 태그타입

	UPROPERTY(EditAnywhere, Category = "WidgetDialogueUI")
	TSubclassOf<UUserWidget> KorWidgetClass; // 한글 대화텍스트 배경UI 관련 위젯

	UPROPERTY(EditAnywhere, Category = "WidgetDialogueUI")
	TSubclassOf<UUserWidget> EngWidgetClass; // 영어 대화텍스트 배경UI 관련 위젯

	UPROPERTY()
	TObjectPtr<UUserWidget> DialogueWidgetInstance; //동적으로 생성할 UI대화 위젯
	UPROPERTY()
	TObjectPtr<UTextBlock> DialogueTextBlock; //UI대화 위젯 내 텍스트블록
	UPROPERTY()
	TObjectPtr<UTextBlock> NPCNameTextBlock; //UI대화 NPC이름 텍스트블록

	uint8 bIsTalking : 1; //대화중인지변수 

	UPROPERTY()
	TObjectPtr<class URXDialogueData> Eng_DialogueData; // 가져온 영어 대화 데이터
	UPROPERTY()
	TObjectPtr<class URXDialogueData> Kor_DialogueData; // 가져온 한글 대화 데이터

	int32 DialogueIndex; //대화 인덱스

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Dialogue Anim Montage")
	TObjectPtr<UAnimMontage> DialogueMontage; // 대화시플레이할 몽타주

	void PlayDialogueMontage() const;

	// 추가 대화 종료시 BP에서 대화 커스텀 이벤트 추가 구현 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DialoguePopupEvent();
	void DialoguePopupEvent_Implementation(); 
	

	UPROPERTY()
	TObjectPtr<class URXGameInstance> GI; // 게임 인스턴스 참조
};
