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
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

		UWorld* const World = GetWorld();
		World->GetTimerManager().SetTimer(AttackTimer, this, &AMonster::ShotTimerExpired, MonsterStat.FireRate);
	}
	
}
//
// void ACommonMonster::SetActive(bool bInActive)
// {
// 	Super::SetActive(bInActive);
// 	 GetWorldTimerManager().SetTimer(AttackTimer, this
// 	 							, &AMonster::ShotTimerExpired, MonsterStat.FireRate);
// }


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

bool ACommonMonster::GetbeCanFire()
{
	return bCanFire;
}
