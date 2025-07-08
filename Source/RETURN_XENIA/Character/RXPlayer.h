// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RXCharacterBase.h"
#include "Interface/RXPlayerHUDInterface.h"
#include "Interface/RXPlayerInteractionInterface.h"
#include "RXPlayer.generated.h"

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
	virtual void BeginPlay() override;

public: // 카메라섹션 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
	UPROPERTY()
	TObjectPtr<class ARXPlayerController> PlayerController;


public: // 인풋(PlayerMovement) 콜백 함수 섹션
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void CustomJump();
	void StartCrouching();
	void StopCrouching();

	void StartSprinting();
	void StopSprinting();
	uint8 bIsSprinting : 1; // 필요하면 변수로 스프린팅상태 추적

	// 퍼즐 이벤트 관련 함수
	void PuzzelMove(const FInputActionValue& Value);
	void PuzzelReset();
	void PuzzelTab(); // 블라인드퍼즐에서 사용하는 함수

	// 원형 퍼즐 이벤트 관련 함수 및 변수
	uint8 bIsCircularPuzzelMode : 1;
	void ExitCircularPuzzel();
	void RotateCP_CounterClockWise();
	void RotateCP_ClockWise();
	void ChangeSelectedWheel();

	// 매듭문자 달기 이벤트 관련 함수 및 변수
	void HangKnotChar();
	void ExitHangingKnot();

protected: // 플레이어 사망 관련 함수 및 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	// 보스맵에서 플레이어 사망시 플레이할 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontageInBossMap;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsBossStage = false;
	void SetDead();
	void PlayDeadAnimation();
	void DeadRespawn();

public: // 스텟 섹션 (HP,Shield 관련)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URXPlayerStatComponent> Stat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> HitMontage;

	UPROPERTY() // 참조하는 게임인스턴스 변수
	TObjectPtr<class URXGameInstance> GI;
public: 
	// 탐지 함수 섹션
	bool UpdateDetectedActor(); //감지
	void ResetDetectedActors();  //리셋

	// NPC 대화 관련 NPC 탐지 변수 
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class ARXNonPlayer> DetectedNPC;

	// 탐지 텔레포트 엑터 변수
	UPROPERTY()
	TObjectPtr<class ARXLevelTeleportActor> DetectedTeleportActor;

	// 퍼즐 이벤트 엑터 변수
	UPROPERTY()
	TObjectPtr<class ARXPuzzelBase> DetectedPuzzelActor;
	UPROPERTY()
	TObjectPtr<class ARXCircularPuzzelBase> DetectedCircularPuzzelActor;

	// 매듭 행거
	UPROPERTY()
	TObjectPtr<class ARXKnotHanger> DetectedKnotHangerActor;

	// 퍼즐이벤트 플레이어 포지션 셋팅 함수
	void MoveToTagLocation(FName TagName, float ZOffSet);

protected:
	// PlayerHUD 인터페이스 가상함수 오버라이드 구현 섹션
	virtual void SetupHUDWidget(class URXHUDWidget* InHUDWidget) override;

public:
	// Interaction  인터페이스 가상함수 오버라이드 구현 섹션
	virtual void Interact_IA_EKey() override;
	virtual void Interact_IA_TabKey() override;

};
