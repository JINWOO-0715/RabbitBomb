// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"
#include "Kismet/GameplayStatics.h"

ABossMonster::ABossMonster()
{
	
}

void ABossMonster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (Active)
	{
		AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FRotator NewRotation = (Player->GetActorLocation() - GetActorLocation()).Rotation();
		NewRotation.Pitch=0.f;
		NewRotation.Roll=0.f;
		
		SetActorRotation(NewRotation);
		Mfire();
	}
}

void ABossMonster::Mfire()
{
	
		
	if(bCanFire)
	{
		
		bCanFire = false;
		
		int BossBulletPattern = FMath::RandRange(0, 4);
		switch (BossBulletPattern)
		{
		case 0:
			AttackPatternComponent->TargetShot(UGameplayStatics::GetPlayerPawn(GetWorld(), 0), MonsterStat.BulletSpeed);
			break;
		case 1:
			AttackPatternComponent->StarShot();
			break;
		case 2:
			AttackPatternComponent->CirCleShot();
			break;
		case 3:
			AttackPatternComponent->SevenStraightShot(GetActorForwardVector());
			break;
		case 4:
			AttackPatternComponent->FireStraightRandom();
			break;
		default:
			break;
		}
	}
}

void ABossMonster::InitMonster(const FBossMonsterData* mMonsterStat)
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
