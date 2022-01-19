// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerMonster.h"

ATowerMonster::ATowerMonster()
{
}

void ATowerMonster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATowerMonster::Mfire()
{
	
}

void ATowerMonster::InitMonster(const FTowerMonsterData* mMonsterStat)
{
	if(mMonsterStat)
	{
		//�޽ü���
		MonsterMeshComponent->SetStaticMesh(mMonsterStat->MonsterMesh);
		//�Ѿ˼ӵ�
		MonsterStat.BulletSpeed = mMonsterStat->Stat.BulletSpeed;
		//���ݼӵ�
		MonsterStat.FireRate = mMonsterStat->Stat.FireRate;
		// ����HP
		MonsterStat.MonsterHP =  mMonsterStat->Stat.MonsterHP;
		//�Ѿ� �Ŀ�
		MonsterStat.BulletPower = mMonsterStat->Stat.BulletPower;
		//���� �̼�
		MonsterStat.MoveSpeed = mMonsterStat->Stat.MoveSpeed;
		//
		MonsterStat.BulletLifeSpan = mMonsterStat->Stat.BulletLifeSpan;	
	}

}
