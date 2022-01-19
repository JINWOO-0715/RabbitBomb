// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonMonster.h"
#include "Kismet/GameplayStatics.h"

ACommonMonster::ACommonMonster()
{
	
}

void ACommonMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(Active)
	{
		
		Mfire();
		
		MoveToTarget();
	}
	
}

void ACommonMonster::Mfire()
{
	
	if(bCanFire)
	{
		
		bCanFire = false; 
		const AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		AttackPatternComponent->TargetShot(Player, MonsterStat.BulletSpeed);
	}
	
}



void ACommonMonster::MoveToTarget()
{

		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // 벡터

		const FVector Movement = Dir * MonsterStat.MoveSpeed; //

		FRotator NewRotation = Movement.Rotation();
		//FTransform d (Movement,NewRotation,NULL;
		SetActorRotation(NewRotation);
		//AddActorWorldOffset(Movement,true,nullptr);
		RootComponent->MoveComponent(Movement, NewRotation, true);

}

void ACommonMonster::InitMonster(const FCommonMonsterData* mMonsterStat)
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
