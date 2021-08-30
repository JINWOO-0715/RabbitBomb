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


		// �нú���
		if (!PlayerSkillRowData->IsActiveSkill)
		{
			SetPlayerBuff(PlayerSkillRowData);
		}

		//��Ƽ����
		if (PlayerSkillRowData->IsActiveSkill)
		{
			SetPlayerBuff(PlayerSkillRowData);
		}

		// ������Ʈ�� ������ fname�� �ش��ϴ°� �����Ѵ�.

		//������ ���� �� �� datatble�� �����???


		//������ ������Ʈ�� �˾Ƽ� ��ų�� �����Ѵ�.

		// ������Ʈ �������� �Լ�
		return;
	}


	//��ų�� ������ ��ų ������
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
	// �Ʒ��� ��� ��ų �߰��ϸ��!

	
}

void USkillComponent::SkillLevelUp(FName mSkillName)
{
	if (*HasSkill.Find(mSkillName) > 0)
	{
		*HasSkill.Find(mSkillName) = 2;

		// ��ų ������ �����ϴ� �Լ�
	}
	if (*HasSkill.Find(mSkillName) > 1)
	{
		*HasSkill.Find(mSkillName) = 3;
	}
}

void USkillComponent::ActiveSkill()
{
}
