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
		bCanFire = false; // ����
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
				if (i > 30)
				{
					monsterBullet->SetActive(false);
				}
			}
		}
	}
}
