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

void USkillComponent::AddSkill(FName const mSkillName)
{
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(mSkillName);


	// 없다면 스킬추가.
	if (!HasSkill.Find(mSkillName))
	{
		HasSkill.Add(mSkillName, 1);
		SetPlayerBuff(PlayerSkillRowData);
	}
	// 있는 스킬이라면
	else
	{
		if (!PlayerSkillRowData->IsActiveSkill)
		{
			//스킬이 있으면 스킬 레벨업
			SkillLevelUp(mSkillName);
			SetPlayerBuff(PlayerSkillRowData, HasSkill[mSkillName]);
		}
		// 패시브라면
		//액티브라면
		if (PlayerSkillRowData->IsActiveSkill)
		{
			//스킬이 있으면 스킬 레벨업
			//SkillLevelUp(mSkillName);
			//		SetPlayerBuff(PlayerSkillRowData);
			//액티브 활성화
		}
	}
	

		// 오브젝트에 버프중 fname에 해당하는걸 적용한다.

		//레벨에 따른 건 또 datatble을 만든다???


		//가져온 오브젝트가 알아서 스킬을 적용한다.

		// 오브젝트 가져오는 함수




}

void USkillComponent::SetPlayerActiveSkill(FPlayerSkillRow* mSkillRow)
{
	
	
}
void USkillComponent::SetPlayerBuff(FPlayerSkillRow* mSkillRow , int mSkillLevel)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, mSkillRow->SKillName.ToString());

	if (mSkillRow->SKillName == FName("FasterRabbit"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,  FString::FromInt(mSkillLevel));
		AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		float TempSpeed = PlayerPawn->GetMoveSpeed();
		// 레벨 값을 가져와서 적용한다.
		
		TempSpeed *= mSkillRow->SkillLevelMap[mSkillLevel];
		PlayerPawn->SetMoveSpeed(TempSpeed);

		float TempFireRate = PlayerPawn->GetFireRate();
		
		TempFireRate *= (2-mSkillRow->SkillLevelMap[mSkillLevel]);
		PlayerPawn->SetFireRate(TempFireRate);
	}

	if (mSkillRow->SKillName == FName("PowerfulRabbit"))
	{
		AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		float TempBulletPower = PlayerPawn->GetBulletPower();
		TempBulletPower *= mSkillRow->SkillLevelMap[mSkillLevel];
		PlayerPawn->SetBulletPower(TempBulletPower);
	}
	// 아래로 계속 스킬 추가하면됌!

	
}

void USkillComponent::SkillLevelUp(FName mSkillName)
{
	// 있는스킬이라면.

	if(HasSkill[mSkillName]<3)
	 	HasSkill[mSkillName]++;

}

void USkillComponent::ActiveSkill()
{
}
