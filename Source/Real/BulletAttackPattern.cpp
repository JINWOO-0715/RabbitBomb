// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAttackPattern.h"
#include "RealGameModeBase.h"


// Sets default values for this component's properties
UBulletAttackPattern::UBulletAttackPattern()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBulletAttackPattern::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



void UBulletAttackPattern::FireShot(const AActor* Target, const AActor* Me, const float BulletSpeed)
{
	// 그냥 1발 발사.


	//UWorld* const World = GetWorld();
	ARealGameModeBase* Gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = Gm->BulletPooler->GetPooledBullet();
	if (Bullet)
	{
		
		FVector Dir = Target->GetActorLocation()- Me->GetActorLocation();
		Dir.Normalize(); // 벡터
		const FVector Movement = Dir * BulletSpeed; 
		// 가지고있는 액터 누구?
		Bullet->SetOwnerActor(Me);
		// 가지고있는 총알위치
		Bullet->SetActorLocation(Me->GetActorLocation());
		// 총알 속도
		Bullet->SetVelocity(Movement);
		// 알아서 살아지게하고
		Bullet->SetLifeSpan();
		// 활성화시킨다.
		Bullet->SetActive(true);
	}
	//World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);

}

