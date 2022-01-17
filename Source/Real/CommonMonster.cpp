// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonMonster.h"
#include "Kismet/GameplayStatics.h"

void ACommonMonster::Tick(float DeltaTime)
{

	if(Active)
	{
		Mfire();
	}
	
}

void ACommonMonster::Mfire()
{
	
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


void ACommonMonster::MoveToTarget()
{

		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // บคลอ

		const FVector Movement = Dir * MonsterStat.MoveSpeed; //

		FRotator NewRotation = Movement.Rotation();
		//FTransform d (Movement,NewRotation,NULL;
		SetActorRotation(NewRotation);
		//AddActorWorldOffset(Movement,true,nullptr);
		RootComponent->MoveComponent(Movement, NewRotation, true);

}
