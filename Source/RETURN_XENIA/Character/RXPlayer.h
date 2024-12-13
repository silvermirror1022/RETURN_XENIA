// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RXCharacterBase.h"
#include "Interface/RXPlayerHUDInterface.h"
#include "Interface/RXPlayerInteractionInterface.h"
#include "RXPlayer.generated.h"

class URXInputData;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class RETURN_XENIA_API ARXPlayer : public ARXCharacterBase, public IRXPlayerHUDInterface, public IRXPlayerInteractionInterface
{
	GENERATED_BODY()
	
public:
	ARXPlayer();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

protected: // 카메라섹션
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;

protected: // 인풋 콜백 함수 섹션
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprinting();
	void StopSprinting();
	void PuzzelMove(const FInputActionValue& Value);

protected: // 플레이어 사망 관련 함수 및 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

protected: // 스텟 섹션 (HP,Shield 관련)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URXPlayerStatComponent> Stat;

	UPROPERTY() // 참조하는 게임인스턴스 변수
	TObjectPtr<class URXGameInstance> GI;
public: 
	// 탐지 함수 섹션
	void UpdateDetectedActor(); //감지
	void ResetDetectedActors();  //리셋

	// NPC 대화 관련 NPC 탐지 변수 
	UPROPERTY()
	TObjectPtr<class ARXNonPlayer> DetectedNPC;

	// 탐지 텔레포트 엑터 변수
	UPROPERTY()
	TObjectPtr<class ARXLevelTeleportActor> DetectedTeleportActor;

	// 퍼즐 이벤트 엑터 변수
	UPROPERTY()
	TObjectPtr<class ARXPuzzelBase> DetectedPuzzelActor;

	// 퍼즐이벤트 플레이어 포지션 셋팅 함수
	void MoveToTagLocation(FName TagName, float ZOffSet);

protected:
	// PlayerHUD 인터페이스 가상함수 오버라이드 구현 섹션
	virtual void SetupHUDWidget(class URXHUDWidget* InHUDWidget) override;

public:
	// Interaction  인터페이스 가상함수 오버라이드 구현 섹션
	virtual void Interact_IA_EKey() override;
	virtual void Interact_IA_EnterKey() override;

};
