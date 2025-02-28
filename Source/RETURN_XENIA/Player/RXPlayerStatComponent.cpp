// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RXPlayerStatComponent.h"
#include "System/RXGameInstance.h"
#include "Character/RXPlayer.h"
#include "RXDebugHelper.h"
#include "Kismet/GameplayStatics.h"

URXPlayerStatComponent::URXPlayerStatComponent()
{
	MaxShield = 1;
	MaxHp = 3;
	bIsShieldRegenActive = false;
	bWantsInitializeComponent = true; //InitializeComponent 함수 호출을 위해
	bIsImmortal = false;

	PrimaryComponentTick.bCanEverTick = true; // 틱 활성화
	PrimaryComponentTick.bStartWithTickEnabled = true; 
}

void URXPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
}
void URXPlayerStatComponent::InitializeStatComponent()
{

	if (GetGameInstance())
	{
		CurrentHp = GI->GetGI_Hp();
		CurrentShield = GI->GetGI_Shield();
	}

	if (GetGameInstance())
	{
		if (GI->IsProfileStatusAcquired("Kaira_necklace"))
		{
			bHasShield = true;
			SetComponentTickEnabled(true); // 틱 활성화

			if (CurrentShield == 0) StartShieldRegen();
		}
		else
		{
			bHasShield = false;
		}
		CurrentHp = GI->GetGI_Hp();
		CurrentShield = GI->GetGI_Shield();
		if (OnPlayerHpAndShieldChanged.IsBound())
		{
			OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);
		}
	}
}

void URXPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false); 

	InitializeStatComponent();
}
void URXPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShieldRegenTimer.IsValid())
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(ShieldRegenTimer);

		int32 CurrentSecIndex = FMath::Clamp(static_cast<int32>(8.0f-RemainingTime), 1, 8);
		//D(FString::Printf(TEXT("Current cooltime: %d"), CurrentSecIndex));
		// 델리게이트 호출로 UI 업데이트
		OnPlayerShieldSecRegenChanged.Broadcast(CurrentSecIndex);
	}
}
URXGameInstance* URXPlayerStatComponent::GetGameInstance()
{
	if (!GI)
	{
		GI = Cast<URXGameInstance>(GetWorld()->GetGameInstance());
		if (!GI)
		{
			UE_LOG(LogTemp, Error, TEXT("RXGameInstance is still null!"));
		}
	}
	return GI;
}
void URXPlayerStatComponent::SetHpToGI(int32 NewHp)
{
	CurrentHp = NewHp;
	GI->SetGI_Hp(NewHp);
    OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);
}
void URXPlayerStatComponent::SetShieldToGI(int32 NewShield)
{
	CurrentShield = NewShield;
	GI->SetGI_Shield(NewShield);
    OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);
}

void URXPlayerStatComponent::ApplyDamage(int32 InDamage)
{
	/*
	 * 주의: 이 컴포넌트는 C++에서 Player에 추가하지 않았음.
	 * 블루프린트 BP_Player에서 추가했음. 데미지사용함수를 쓸 때 BP로 캐스팅해야 무적이 정상 작동함.
	 * 단순 트리거 태스팅은 RXPlayer로 사용해도 됨!
	 */
	if (bIsImmortal || InDamage <= 0)
	{
		D(FString::Printf(TEXT("Immortal!")));
		return; // 무적 상태면 데미지 적용 안 함
	}

	D(FString::Printf(TEXT("damaged!")));

	if (HitSound)
	{
		UGameplayStatics::PlaySound2D(this, HitSound);
	}

	// 무적 상태 활성화
	bIsImmortal = true;
	GetWorld()->GetTimerManager().SetTimer(ImmortalTimer, this, &URXPlayerStatComponent::ResetImmortalState, ImmortalTime, false); // 0.5초 후 해제

	// 무적 시 머터리얼 깜빡임 시작
	//StartMaterialFlash();

	// 무적 상태 진입 시 플레이어 머터리얼 변경 (빨간색)
	if (AActor* OwnerActor = GetOwner())
	{
		ARXPlayer* Player = Cast<ARXPlayer>(OwnerActor);
		if (Player && RedMaterial)
		{
			// 메시의 첫 번째 머터리얼 슬롯(인덱스 0)을 빨간색 머터리얼로 교체
			Player->GetMesh()->SetMaterial(0, RedMaterial);
		}
	}
	// 플레이어가 데미지를 입었을 때 호출
	if (bIsShieldRegenActive)
	{
		// 기존 쉴드 리젠 타이머 초기화
		GetWorld()->GetTimerManager().ClearTimer(ShieldRegenTimer);
		bIsShieldRegenActive = false;
	}

	int32 DamageLeft = InDamage;

	// 쉴드가 있는 경우
	if (bHasShield && CurrentShield > 0)
	{
		const int32 ShieldDamage = FMath::Min(DamageLeft, CurrentShield);
		SetShieldToGI(CurrentShield - ShieldDamage); // 쉴드 감소
		DamageLeft -= ShieldDamage;
	}

	// 남은 데미지를 체력에 적용
	if (DamageLeft > 0)
	{
		SetHpToGI(CurrentHp - DamageLeft);
		OnPlayerHpAndShieldChanged.Broadcast(CurrentHp, CurrentShield);

		// 체력이 0 이하가 되면 델리게이트 호출
		if (CurrentHp <= 0)
		{
			OnPlayerHpZero.Broadcast();
		}
	}

	// 쉴드 리젠 처리
	if (bHasShield && CurrentShield == 0 && !bIsShieldRegenActive)
	{
		StartShieldRegen();
	}
}
void URXPlayerStatComponent::ApplyHealing(int32 InHealAmount)
{
	// 체력 회복
	if (InHealAmount > 0)
	{
		int32 NewHp = FMath::Clamp(CurrentHp + InHealAmount, 0, MaxHp); // 최대 HP 초과 방지
		SetHpToGI(NewHp);
	}

	// 여동생 방패가 있을 경우 방패 100% 회복
	if (bHasShield)
	{
		SetShieldToGI(MaxShield); // 방패를 최대치로 설정
	}

	GetWorld()->GetTimerManager().ClearTimer(ShieldRegenTimer);
	OnPlayerShieldFull.Broadcast();
}
void URXPlayerStatComponent::StartShieldRegen()
{
    if (bIsShieldRegenActive) return;

    bIsShieldRegenActive = true;

	// 레벨이동에 객체 UI,델리게이트 소멸 재생성 문제 해결을 위한 약한 참조 람다 활용
	TWeakObjectPtr<URXPlayerStatComponent> WeakThis(this);
    GetWorld()->GetTimerManager().SetTimer(ShieldRegenTimer, [WeakThis]()
        {
			if (WeakThis.IsValid())
			{
				WeakThis->ShieldRegenAction();
			}
        }, 8.00f, false);
}
void URXPlayerStatComponent::ShieldRegenAction()
{
	SetShieldToGI(MaxShield); 
	bIsShieldRegenActive = false;
}

/**/void URXPlayerStatComponent::ResetImmortalState()
{
	bIsImmortal = false;

	/*// 타이머가 아직 남아있다면 깜빡임 타이머를 종료
	if (GetWorld()->GetTimerManager().IsTimerActive(MaterialFlashTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(MaterialFlashTimer);
	}*/
	// 기본 머터리얼로 복원
	if (AActor* OwnerActor = GetOwner())
	{
		ARXPlayer* Player = Cast<ARXPlayer>(OwnerActor);
		if (Player && DefaultMaterial)
		{
			Player->GetMesh()->SetMaterial(0, DefaultMaterial);
		}
	}
	D(FString::Printf(TEXT("Current Health: %d !"), GetCurrentHp()));
}

/*void URXPlayerStatComponent::StartMaterialFlash()
{
	// 깜빡임 카운트를 0으로 초기화
	FlashToggleCount = 0;

	// 0.5초 동안 5번 깜빡이려면 총 10번 토글, 간격은 0.5초 / 10 = 0.05초
	GetWorld()->GetTimerManager().SetTimer(MaterialFlashTimer, this, &URXPlayerStatComponent::ToggleMaterialFlash, 0.1f, true);
}

void URXPlayerStatComponent::ToggleMaterialFlash()
{
	// GetOwner()를 통해 ARXPlayer에 접근
	if (AActor* OwnerActor = GetOwner())
	{
		ARXPlayer* Player = Cast<ARXPlayer>(OwnerActor);
		if (Player)
		{
			// 짝수이면 빨간색, 홀수이면 기본 머터리얼로 교체
			if (FlashToggleCount % 2 == 0)
			{
				if (RedMaterial)
				{
					Player->GetMesh()->SetMaterial(0, RedMaterial);
				}
			}
			else
			{
				// 기본 머터리얼 복원
				if (DefaultMaterial)
				{
					Player->GetMesh()->SetMaterial(0, DefaultMaterial);
				}
			}
		}
	}
	FlashToggleCount++;

	// 총 10번 토글 후 타이머 종료 및 기본 머터리얼 확실히 복원
	if (FlashToggleCount >= 5)
	{
		GetWorld()->GetTimerManager().ClearTimer(MaterialFlashTimer);
		if (AActor* OwnerActor = GetOwner())
		{
			ARXPlayer* Player = Cast<ARXPlayer>(OwnerActor);
			if (Player && DefaultMaterial)
			{
				Player->GetMesh()->SetMaterial(0, DefaultMaterial);
			}
		}
	}
}
*/