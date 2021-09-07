// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonsterActor.h"


ABossMonsterActor::ABossMonsterActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/Boss.Boss"));
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
}

void ABossMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active && !isStun)
	{
		FireShot();
	}
}

void ABossMonsterActor::FireShot()
{
	if (bCanFire)
	{
		bCanFire = false; // 끊고
		UWorld* const World = GetWorld();
		ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
		if (monsterBullet && World)
		{
			for (int i = 0; i < 36; i++)
			{
				monsterBullet = gm->BulletPooler->GetPooledBullet();
				// 몬스터 위치
				FVector Location = GetActorLocation();
				// 원 (x,y)
				FVector Circledir(cos((2 * PI * i) / 36), sin((2 * PI * i) / 36), 0.f);
				// 반지금이 100인 원(x,y)
				Circledir *= 100;
				// 내위치에 그 위치를 더해서
				Location += Circledir;
				// 방향은 먼위치 - 내위치
				FVector Dir = Location - GetActorLocation();
				// 방향벡터 
				Dir.Normalize();

				const FVector FMovement = Dir * BulletSpeed; //
				// 가지고있는 액터 누구?
				monsterBullet->SetOwnerActor(this);
				// 가지고있는 총알위치
				monsterBullet->SetActorLocation(Location);

				//총알 속도
				monsterBullet->SetVelocity(FMovement);
				// 알아서 살아지게하고
				monsterBullet->SetLifeSpan();
				// 활성화시킨다.
				monsterBullet->SetActive(true);
				if (i > 30)
				{
					monsterBullet->SetActive(false);
				}
			}
		}
	}
}
