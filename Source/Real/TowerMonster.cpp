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
		//메시설정
		MonsterMeshComponent->SetStaticMesh(mMonsterStat->MonsterMesh);
		//총알속도
		MonsterStat.BulletSpeed = mMonsterStat->Stat.BulletSpeed;
		//공격속도
		MonsterStat.FireRate = mMonsterStat->Stat.FireRate;
		// 몬스터HP
		MonsterStat.MonsterHP =  mMonsterStat->Stat.MonsterHP;
		//총알 파워
		MonsterStat.BulletPower = mMonsterStat->Stat.BulletPower;
		//몬스터 이속
		MonsterStat.MoveSpeed = mMonsterStat->Stat.MoveSpeed;
		//
		MonsterStat.BulletLifeSpan = mMonsterStat->Stat.BulletLifeSpan;	
	}

}
