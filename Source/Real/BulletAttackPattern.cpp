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



void UBulletAttackPattern::FireShot(const AActor* Target, const float BulletSpeed)
{
	// 1발 타겟을 향해 발사.

	//UWorld* const World = GetWorld();
	ARealGameModeBase* Gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = Gm->BulletPooler->GetPooledBullet();
	const AActor* Me = GetOwner();
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

void UBulletAttackPattern::CirCleShot(const float BulletSpeed)
{

	ARealGameModeBase* Gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = Gm->BulletPooler->GetPooledBullet();
	const AActor* Me = GetOwner();
	UWorld* const World = GetWorld();
	if (World)
	{
		for (int i = 0; i < 36; i++)
		{
			Bullet = Gm->BulletPooler->GetPooledBullet();
			// 몬스터 위치
			FVector Location = Me->GetActorLocation();
			// 원 (x,y)
			FVector Circledir(cos((2 * PI * i) / 36), sin((2 * PI * i) / 36), 0.f);
			// 반지름이 100인 원(x,y)
			Circledir *= 100;
			// 내위치에 그 위치를 더해서
			Location += Circledir;
			// 방향은 먼위치 - 내위치
			FVector Dir = Location - Me->GetActorLocation();
			// 방향벡터 
			Dir.Normalize();

			const FVector FMovement = Dir * BulletSpeed; //
			// 가지고있는 액터 누구?
			Bullet->SetOwnerActor(Me);
			// 가지고있는 총알위치
			Bullet->SetActorLocation(Location);

			//총알 속도
			Bullet->SetVelocity(FMovement);
			// 알아서 살아지게하고
			Bullet->SetLifeSpan();
			// 활성화시킨다.
			Bullet->SetActive(true);

		}
	}
}

