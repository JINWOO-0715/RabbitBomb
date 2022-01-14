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
	// 1�� Ÿ���� ���� �߻�.

	//UWorld* const World = GetWorld();
	ARealGameModeBase* Gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = Gm->BulletPooler->GetPooledBullet();
	const AActor* Me = GetOwner();
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
			// ���� ��ġ
			FVector Location = Me->GetActorLocation();
			// �� (x,y)
			FVector Circledir(cos((2 * PI * i) / 36), sin((2 * PI * i) / 36), 0.f);
			// �������� 100�� ��(x,y)
			Circledir *= 100;
			// ����ġ�� �� ��ġ�� ���ؼ�
			Location += Circledir;
			// ������ ����ġ - ����ġ
			FVector Dir = Location - Me->GetActorLocation();
			// ���⺤�� 
			Dir.Normalize();

			const FVector FMovement = Dir * BulletSpeed; //
			// �������ִ� ���� ����?
			Bullet->SetOwnerActor(Me);
			// �������ִ� �Ѿ���ġ
			Bullet->SetActorLocation(Location);

			//�Ѿ� �ӵ�
			Bullet->SetVelocity(FMovement);
			// �˾Ƽ� ��������ϰ�
			Bullet->SetLifeSpan();
			// Ȱ��ȭ��Ų��.
			Bullet->SetActive(true);

		}
	}
}

