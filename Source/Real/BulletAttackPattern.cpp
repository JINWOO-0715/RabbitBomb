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
	// �׳� 1�� �߻�.


	//UWorld* const World = GetWorld();
	ARealGameModeBase* Gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = Gm->BulletPooler->GetPooledBullet();
	if (Bullet)
	{
		
		FVector Dir = Target->GetActorLocation()- Me->GetActorLocation();
		Dir.Normalize(); // ����
		const FVector Movement = Dir * BulletSpeed; 
		// �������ִ� ���� ����?
		Bullet->SetOwnerActor(Me);
		// �������ִ� �Ѿ���ġ
		Bullet->SetActorLocation(Me->GetActorLocation());
		// �Ѿ� �ӵ�
		Bullet->SetVelocity(Movement);
		// �˾Ƽ� ��������ϰ�
		Bullet->SetLifeSpan();
		// Ȱ��ȭ��Ų��.
		Bullet->SetActive(true);
	}
	//World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);

}

