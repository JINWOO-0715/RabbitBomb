// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonsterActor.h"


ABossMonsterActor::ABossMonsterActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/Boss.Boss"));
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	AttackCount=0;
}

void ABossMonsterActor::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	if (Active && !isStun)
	{
		
		FireShot();
	}
}

void ABossMonsterActor::FireShot()
{
	if (bCanFire)
	{
		BossBulletPattern =FMath::RandRange(0, 2);
		FireRate = FMath::RandRange(1.f, 2.5f);
		switch (BossBulletPattern)
		{
		case 0:
			// 0.3�� �� 5��
			FireCircleShot();
			break;
		case 1:
			// 0.3�� �� 3��
			FireStraight();
			break;
		case 2:
			// 0.3�� �� 5��
			FireCircularsector();
			break;
		case 3:
			
			break;
		case 4:
			break;
		default:
			break;
		}
		bCanFire = false; // ����

	}
}

void ABossMonsterActor::FireCircleShot()
{
	UWorld* const World = GetWorld();
	
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
	
	if (monsterBullet && World)
	{
		
		for (int i = 0; i < 36; i++)
		{
			monsterBullet = gm->BulletPooler->GetPooledBullet();
			// ���� ��ġ
			FVector Location = GetActorLocation();
			// �� (x,y)
			FVector Circledir(cos((2 * PI * i) / 36), sin((2 * PI * i) / 36), 0.f);
			// �������� 100�� ��(x,y)
			Circledir *= 100;
			// ����ġ�� �� ��ġ�� ���ؼ�
			Location += Circledir;
			// ������ ����ġ - ����ġ
			FVector Dir = Location - GetActorLocation();
			// ���⺤�� 
			Dir.Normalize();

			const FVector FMovement = Dir * BulletSpeed; //
			// �������ִ� ���� ����?
			monsterBullet->SetOwnerActor(this);
			// �������ִ� �Ѿ���ġ
			monsterBullet->SetActorLocation(Location);

			//�Ѿ� �ӵ�
			monsterBullet->SetVelocity(FMovement);
			// �˾Ƽ� ��������ϰ�
			monsterBullet->SetLifeSpan();
			// Ȱ��ȭ��Ų��.
			monsterBullet->SetActive(true);

		}
		if(AttackCount<5)
		{
			
			AttackCount++;
			World->GetTimerManager().SetTimer(AttackTimer, this, &ABossMonsterActor::FireCircleShot, 0.5f);
		}
		else
		{
		
			AttackCount=0;
			World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);	
		}
		
	}
	
}

void ABossMonsterActor::FireStraight()
{
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
	for (int i = 0; i < 5; i++)
	{
		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // ����

		monsterBullet = gm->BulletPooler->GetPooledBullet();
		const FVector randomV(FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(0.f, 2.f), 0.f);
		Dir += randomV;
		Dir.Normalize();
		const FVector FMovement = Dir * BulletSpeed; //
		// �������ִ� ���� ����?
		monsterBullet->SetOwnerActor(this);
		// �������ִ� �Ѿ���ġ
		monsterBullet->SetActorLocation(GetActorLocation());
		//�Ѿ� �ӵ�
		monsterBullet->SetVelocity(FMovement);
		// �˾Ƽ� ��������ϰ�
		monsterBullet->SetLifeSpan();
		// Ȱ��ȭ��Ų��.
		monsterBullet->SetActive(true);
		
	}
	if(AttackCount<5)
	{

		AttackCount++;
		World->GetTimerManager().SetTimer(AttackTimer, this, &ABossMonsterActor::FireStraight, 0.3f);
	}
	else
	{
		AttackCount=0;
		World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);	
	}
	
}

void ABossMonsterActor::FireCircularsector()
{


	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(3));
	float parameter = -0.5f;
	FVector FireDir = GetActorForwardVector();
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
	
	for (int i = 0; i < 10; i++)
	{

		if (monsterBullet && World)
		{
			monsterBullet = gm->BulletPooler->GetPooledBullet();
			monsterBullet->SetActive(true);
			monsterBullet->SetOwnerActor(this);
			monsterBullet->SetActorLocation(GetActorLocation());
			FVector RotationVector(FireDir.X * cos(parameter) - FireDir.Y * sin(parameter),
								FireDir.X * sin(parameter) + FireDir.Y * cos(parameter), 0.f);
			RotationVector.Normalize();
			parameter += 0.1f;
			const FVector Movement = RotationVector * 1000.f; // 
			monsterBullet->SetVelocity(Movement);
			monsterBullet->SetLifeSpan();
						
		}
				
	}
	if(AttackCount<5)
	{

		AttackCount++;
		World->GetTimerManager().SetTimer(AttackTimer, this, &ABossMonsterActor::FireCircularsector, 0.3f);
	}
	else
	{
		AttackCount=0;
		World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);	
	}

}
