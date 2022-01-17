// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonMonster.h"
#include "Kismet/GameplayStatics.h"

void ACommonMonster::Tick(float DeltaTime)
{

	if(Active)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
		Mfire();
	}
	
}

void ACommonMonster::Mfire()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	if(bCanFire)
	{
		bCanFire = false; 

		const AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		AttackPatternComponent->TargetShot(Player, MonsterStat.BulletSpeed);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

		UWorld* const World = GetWorld();
		World->GetTimerManager().SetTimer(AttackTimer, this, &AMonster::ShotTimerExpired, MonsterStat.FireRate);
	}
	
}
