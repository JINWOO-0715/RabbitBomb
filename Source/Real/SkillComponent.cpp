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


	// ���ٸ� ��ų�߰�.
	if (!HasSkill.Find(mSkillName))
	{
		HasSkill.Add(mSkillName, 1);
		SetPlayerBuff(PlayerSkillRowData);
	}
	// �ִ� ��ų�̶��
	else
	{
		if (!PlayerSkillRowData->IsActiveSkill)
		{
			//��ų�� ������ ��ų ������
			SkillLevelUp(mSkillName);
			SetPlayerBuff(PlayerSkillRowData, HasSkill[mSkillName]);
		}
		// �нú���
		//��Ƽ����
		if (PlayerSkillRowData->IsActiveSkill)
		{
			//��ų�� ������ ��ų ������
			//SkillLevelUp(mSkillName);
			//		SetPlayerBuff(PlayerSkillRowData);
			//��Ƽ�� Ȱ��ȭ
		}
	}
	

		// ������Ʈ�� ������ fname�� �ش��ϴ°� �����Ѵ�.

		//������ ���� �� �� datatble�� �����???


		//������ ������Ʈ�� �˾Ƽ� ��ų�� �����Ѵ�.

		// ������Ʈ �������� �Լ�




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
		// ���� ���� �����ͼ� �����Ѵ�.
		
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
	// �Ʒ��� ��� ��ų �߰��ϸ��!

	
}

void USkillComponent::SkillLevelUp(FName mSkillName)
{
	// �ִ½�ų�̶��.

	if(HasSkill[mSkillName]<3)
	 	HasSkill[mSkillName]++;

}

void USkillComponent::ActiveSkill()
{
}
