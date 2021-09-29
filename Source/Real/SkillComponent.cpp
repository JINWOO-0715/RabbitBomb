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

	
	// ��ų�� �ִٸ�.
}

//
// void USkillComponent::AddSkill(FName const mSkillName)
// {
// 	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
// 	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(mSkillName);
//
//
// 	// ���ٸ� ��ų�߰�.
// 	if (!HasSkill.Find(mSkillName))
// 	{
// 		HasSkill.Add(mSkillName, 0);
// 		ActiveSkill(PlayerSkillRowData, mSkillName);
// 	}
// 		// �ִ� ��ų�̶��
// 	else
// 	{
// 		ActiveSkill(PlayerSkillRowData, mSkillName);
// 	}
//
//
// 	// ������Ʈ�� ������ fname�� �ش��ϴ°� �����Ѵ�.
//
// 	//������ ���� �� �� datatble�� �����???
//
//
// 	//������ ������Ʈ�� �˾Ƽ� ��ų�� �����Ѵ�.
//
// 	// ������Ʈ �������� �Լ�
// }

void USkillComponent::AddSkill(int mSkillInt)
{
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(mSkillInt);

	FName mSkillName =PlayerSkillRowData->SKillName;

	// ���ٸ� ��ų�߰�.
	
	if (!HasSkill.Find(mSkillName))
	{
		HasSkill.Add(mSkillName, 0);
		ActiveSkill(PlayerSkillRowData, mSkillName);
	}
	// �ִ� ��ų�̶��
	else
	{
		ActiveSkill(PlayerSkillRowData, mSkillName);
	}


	// ������Ʈ�� ������ fname�� �ش��ϴ°� �����Ѵ�.

	//������ ���� �� �� datatble�� �����???


	//������ ������Ʈ�� �˾Ƽ� ��ų�� �����Ѵ�.

	// ������Ʈ �������� �Լ�
}

void USkillComponent::SetPlayerActiveSkill(FPlayerSkillRow* mSkillRow, int mSkillLevel)
{
	// Ÿ�̸� �߰��ؼ�

	if (mSkillRow->SKillName == FName("IceBullet"))
	{
		
		 if (OwnerActor->ActorHasTag("Player"))
		 {
// iceSkill 1�� 2�� 3��  �߰��ϸ��!
		 	
		

		 	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		 	
		 	UIceSkillComponent* component = NewObject<UIceSkillComponent>(PlayerPawn, UIceSkillComponent::StaticClass());

		 	component->bCanFire=true;
		 	component->OwnerActor =PlayerPawn;
		 	component->Activate(true);
		 	component->RegisterComponent();
		
		
		 }
		

		// �Ѿ��� �ٲ۴�?
	}
	// �۵��ǰ� �Ѵ� 
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
		// ���� ���� �����ͼ� �����Ѵ�.

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
			// ����ϸ� �˾Ƽ� ����Ǵ°� ���̾ ���� ��Ƽ���
			// �Ʒ��� ��ú��� �����ϴ°� �´�??
		}
	}


	// �Ʒ��� ��� ��ų �߰��ϸ��!
}

void USkillComponent::SkillLevelUp(FName mSkillName)
{
	// �ִ½�ų�̶��.

	if (HasSkill[mSkillName] < 3)
		HasSkill[mSkillName]++;
}

void USkillComponent::ActiveSkill(FPlayerSkillRow* mSkillRow, FName mSkillName)
{
	//�нú��
	if (!mSkillRow->IsActiveSkill)
	{
		//��ų�� ������ ��ų ������
		
		SkillLevelUp(mSkillName);
		SetPlayerBuff(mSkillRow, HasSkill[mSkillName]);
	}
	// ��Ƽ��
	if (mSkillRow->IsActiveSkill)
	{
	
		//��ų�� ������ ��ų ������
		SkillLevelUp(mSkillName);
		SetPlayerActiveSkill(mSkillRow, HasSkill[mSkillName]);
		//��Ƽ�� Ȱ��ȭ
	}
}
