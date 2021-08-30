// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "BuffSkill.h"
#include "MainPawn.h"
#include "Kismet/GameplayStatics.h"
#include "RealGameModeBase.h"
// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillComponent::AddSkill(FName mSkillName)
{
	if (!HasSkill.Find(mSkillName))
	{
		HasSkill.Add(mSkillName, 1);
		ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(mSkillName);


		// 패시브라면
		if (!PlayerSkillRowData->IsActiveSkill)
		{
			SetPlayerBuff(PlayerSkillRowData);
		}

		//액티브라면
		if (PlayerSkillRowData->IsActiveSkill)
		{
			SetPlayerBuff(PlayerSkillRowData);
		}

		// 오브젝트에 버프중 fname에 해당하는걸 적용한다.

		//레벨에 따른 건 또 datatble을 만든다???


		//가져온 오브젝트가 알아서 스킬을 적용한다.

		// 오브젝트 가져오는 함수
		return;
	}


	//스킬이 있으면 스킬 레벨업
	SkillLevelUp(mSkillName);
}

void USkillComponent::SetPlayerActiveSkill(FPlayerSkillRow* mSkillRow)
{
	
	
}
void USkillComponent::SetPlayerBuff(FPlayerSkillRow* mSkillRow)
{
	if (mSkillRow->SKillName == "Faster")
	{
		AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		float TempSpeed = PlayerPawn->GetMoveSpeed();
		TempSpeed *= mSkillRow->IncreaseCount;
		PlayerPawn->SetMoveSpeed(TempSpeed);
	}

	if (mSkillRow->SKillName == "Powerful")
	{
		AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		float TempSpeed = PlayerPawn->GetMoveSpeed();
		TempSpeed *= mSkillRow->IncreaseCount;
		PlayerPawn->SetMoveSpeed(TempSpeed);
	}
	// 아래로 계속 스킬 추가하면됌!

	
}

void USkillComponent::SkillLevelUp(FName mSkillName)
{
	if (*HasSkill.Find(mSkillName) > 0)
	{
		*HasSkill.Find(mSkillName) = 2;

		// 스킬 레벨업 적용하는 함수
	}
	if (*HasSkill.Find(mSkillName) > 1)
	{
		*HasSkill.Find(mSkillName) = 3;
	}
}

void USkillComponent::ActiveSkill()
{
}
