// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"

#include "MainPawn.h"
#include "Kismet/GameplayStatics.h"
#include "IceSkillComponent.h"
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

	
	// 스킬이 있다면.
}

//
// void USkillComponent::AddSkill(FName const mSkillName)
// {
// 	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
// 	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(mSkillName);
//
//
// 	// 없다면 스킬추가.
// 	if (!HasSkill.Find(mSkillName))
// 	{
// 		HasSkill.Add(mSkillName, 0);
// 		ActiveSkill(PlayerSkillRowData, mSkillName);
// 	}
// 		// 있는 스킬이라면
// 	else
// 	{
// 		ActiveSkill(PlayerSkillRowData, mSkillName);
// 	}
//
//
// 	// 오브젝트에 버프중 fname에 해당하는걸 적용한다.
//
// 	//레벨에 따른 건 또 datatble을 만든다???
//
//
// 	//가져온 오브젝트가 알아서 스킬을 적용한다.
//
// 	// 오브젝트 가져오는 함수
// }

void USkillComponent::AddSkill(int mSkillInt)
{
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(mSkillInt);

	FName mSkillName =PlayerSkillRowData->SKillName;

	// 없다면 스킬추가.
	
	if (!HasSkill.Find(mSkillName))
	{
		HasSkill.Add(mSkillName, 0);
		ActiveSkill(PlayerSkillRowData, mSkillName);
	}
	// 있는 스킬이라면
	else
	{
		ActiveSkill(PlayerSkillRowData, mSkillName);
	}


	// 오브젝트에 버프중 fname에 해당하는걸 적용한다.

	//레벨에 따른 건 또 datatble을 만든다???


	//가져온 오브젝트가 알아서 스킬을 적용한다.

	// 오브젝트 가져오는 함수
}

void USkillComponent::SetPlayerActiveSkill(FPlayerSkillRow* mSkillRow, int mSkillLevel)
{
	// 타이머 추가해서

	if (mSkillRow->SKillName == FName("IceBullet"))
	{
		
		 if (OwnerActor->ActorHasTag("Player"))
		 {
// iceSkill 1렙 2렙 3렙  추가하면됌!
		 	
		

		 	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		 	
		 	UIceSkillComponent* component = NewObject<UIceSkillComponent>(PlayerPawn, UIceSkillComponent::StaticClass());

		 	component->bCanFire=true;
		 	component->OwnerActor =PlayerPawn;
		 	component->Activate(true);
		 	component->RegisterComponent();
		
		
		 }
		

		// 총알을 바꾼다?
	}
	// 작동되게 한다 
}

void USkillComponent::IceBulletCircle()
{

}

void USkillComponent::SetPlayerBuff(FPlayerSkillRow* mSkillRow, int mSkillLevel)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, mSkillRow->SKillName.ToString());

	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (mSkillRow->SKillName == FName("FasterRabbit"))
	{
		
		float TempSpeed = PlayerPawn->GetMoveSpeed();
		// 레벨 값을 가져와서 적용한다.

		TempSpeed *= mSkillRow->SkillLevelMap[mSkillLevel];
		PlayerPawn->SetMoveSpeed(TempSpeed);

		float TempFireRate = PlayerPawn->GetFireRate();

		TempFireRate *= (2 - mSkillRow->SkillLevelMap[mSkillLevel]);
		PlayerPawn->SetFireRate(TempFireRate);
	}

	if (mSkillRow->SKillName == FName("PowerfulRabbit"))
	{
		float TempBulletPower = PlayerPawn->GetBulletPower();
		TempBulletPower *= mSkillRow->SkillLevelMap[mSkillLevel];
		PlayerPawn->SetBulletPower(TempBulletPower);

		float TempMaxHP = PlayerPawn->GetMaxHp();
		TempMaxHP *= mSkillRow->SkillLevelMap[mSkillLevel];
		PlayerPawn->SetMaxHp(TempMaxHP);
	}


	if (mSkillRow->SKillName == FName("LaunchIncrease"))
	{
		//if(ownerac)
		if (OwnerActor->ActorHasTag("Player"))
		{
	
			PlayerPawn->SetNumberOfShotBullet(mSkillRow->SkillLevelMap[mSkillLevel]);
			// 등록하면 알아서 진행되는건 파이어볼 같은 액티브고
			// 아래는 페시브라고 생각하는게 맞는??
		}
	}


	// 아래로 계속 스킬 추가하면됌!
}

void USkillComponent::SkillLevelUp(FName mSkillName)
{
	// 있는스킬이라면.

	if (HasSkill[mSkillName] < 3)
		HasSkill[mSkillName]++;
}

void USkillComponent::ActiveSkill(FPlayerSkillRow* mSkillRow, FName mSkillName)
{
	//패시브면
	if (!mSkillRow->IsActiveSkill)
	{
		//스킬이 있으면 스킬 레벨업
		
		SkillLevelUp(mSkillName);
		SetPlayerBuff(mSkillRow, HasSkill[mSkillName]);
	}
	// 액티브
	if (mSkillRow->IsActiveSkill)
	{
	
		//스킬이 있으면 스킬 레벨업
		SkillLevelUp(mSkillName);
		SetPlayerActiveSkill(mSkillRow, HasSkill[mSkillName]);
		//액티브 활성화
	}
}
