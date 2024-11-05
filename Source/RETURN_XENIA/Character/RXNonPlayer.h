// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RXCharacterBase.h"
#include "GameplayTagContainer.h"
#include "Interface/RXNPCDialogueInterface.h"
#include "RXNonPlayer.generated.h"

UCLASS()
class RETURN_XENIA_API ARXNonPlayer : public ARXCharacterBase, public IRXNPCDialogueInterface
{
	GENERATED_BODY()

public:
	//가까이가면 상호작용 E UI띄우는 로직은 RXInteractionVisibilityComponent를 통해 구현
	ARXNonPlayer();

protected: 	//RXNPCDialogueInterface Interface Virtual Func override Implementation

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	virtual void StartDialogue() override;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	virtual void DisplayDialogue(UTextBlock* DialogueTextBlock) override;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	virtual void EndDialogue() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCTypeTag")
	FGameplayTag NPCType; //NPC마다 가지고있는 태그타입

	UPROPERTY(EditAnywhere, Category = "WidgetDialogueUI")
	TSubclassOf<UUserWidget> WidgetClass; //대화텍스트 배경UI 관련 위젯
		
	UPROPERTY()
	TObjectPtr<class URXDialogueData> DialogueData; //가져온 대화 데이터

	int32 DialogueIndex; //대화 인덱스

};
