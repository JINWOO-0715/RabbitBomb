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
		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FRotator newrot = (player->GetActorLocation() - GetActorLocation()).Rotation();
		newrot.Pitch=0.f;
		newrot.Roll=0.f;
		
		SetActorRotation(newrot);


		FireShot();
	}
}

void ABossMonsterActor::FireShot()
{
	if (bCanFire)
	{
		BossBulletPattern =4;//FMath::RandRange(0, 2);
		FireRate = FMath::RandRange(1.f, 2.5f);
		switch (BossBulletPattern)
		{
		case 0:
			// 0.3초 총 5번
			FireCircleShot();
			break;
		case 1:
			// 0.3초 총 3번
			FireStraight();
			break;
		case 2:
			// 0.3초 총 5번
			FireStraightRandom();
			break;
		case 3:
			AttackCount = -5;
			FireCircularsector();
			break;
		case 4:
			FireShotStar();
			break;
		default:
			break;
		}
		bCanFire = false; // 끊고

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
	for (int i = 0; i < 8; i++)
	{
		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // 벡터

		monsterBullet = gm->BulletPooler->GetPooledBullet();
		const FVector randomV(FMath::RandRange(-0.5f, 0.5f), FMath::RandRange(0.f, 2.f), 0.f);
		Dir += randomV;
		Dir.Normalize();
		const FVector FMovement = Dir * BulletSpeed; //
		// 가지고있는 액터 누구?
		monsterBullet->SetOwnerActor(this);
		// 가지고있는 총알위치
		monsterBullet->SetActorLocation(GetActorLocation());
		//총알 속도
		monsterBullet->SetVelocity(FMovement);
		// 알아서 살아지게하고
		monsterBullet->SetLifeSpan();
		// 활성화시킨다.
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

void ABossMonsterActor::FireStraightRandom()
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
		World->GetTimerManager().SetTimer(AttackTimer, this, &ABossMonsterActor::FireStraightRandom, 0.3f);
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

	FVector FireDir = GetActorForwardVector();
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();


	if (AttackCount < 5)
	{

		if (monsterBullet && World)
		{
			monsterBullet = gm->BulletPooler->GetPooledBullet();
			monsterBullet->SetActive(true);
			monsterBullet->SetOwnerActor(this);
			monsterBullet->SetActorLocation(GetActorLocation());
			FVector RotationVector(FireDir.X * cos(AttackCount * 0.1f) - FireDir.Y * sin(AttackCount * 0.1f),
			                       FireDir.X * sin(AttackCount * 0.1f) + FireDir.Y * cos(AttackCount * 0.1f), 0.f);
			RotationVector.Normalize();
		

			const FVector Movement = RotationVector * 1000.f; // 
			monsterBullet->SetVelocity(Movement);
			monsterBullet->SetLifeSpan();
		}


		AttackCount++;
		World->GetTimerManager().SetTimer(AttackTimer, this, &ABossMonsterActor::FireCircularsector, 0.2f);
	}
	else
	{
		
		ReverseFireCircularsector();
	}


	
}
void ABossMonsterActor::ReverseFireCircularsector()
{
	

	FVector FireDir = GetActorForwardVector();
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
	
	if(AttackCount>-5)
	{
			if (monsterBullet && World)
			{
				monsterBullet = gm->BulletPooler->GetPooledBullet();
				monsterBullet->SetActive(true);
				monsterBullet->SetOwnerActor(this);
				monsterBullet->SetActorLocation(GetActorLocation());
				FVector RotationVector(FireDir.X * cos(AttackCount*0.1f) - FireDir.Y * sin(AttackCount*0.1f),
									FireDir.X * sin(AttackCount*0.1f) + FireDir.Y * cos(AttackCount*0.1f), 0.f);
				RotationVector.Normalize();
				const FVector Movement = RotationVector * 1000.f; // 
				monsterBullet->SetVelocity(Movement);
				monsterBullet->SetLifeSpan();
						
			}
	
		AttackCount--;
		World->GetTimerManager().SetTimer(AttackTimer, this, &ABossMonsterActor::ReverseFireCircularsector, 0.2f);
	}
	else
	{
		AttackCount=0;
		World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);	
	}


}

void ABossMonsterActor::FireShotStar()
{
	FVector FireDir = GetActorForwardVector();
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
	

	for(int t = -50;t<50;t++)
	{
		monsterBullet = gm->BulletPooler->GetPooledBullet();
		monsterBullet->SetActive(true);
		monsterBullet->SetOwnerActor(this);
	
		FVector V = GetActorLocation();
		
		V.X += 500*cos(2*t) + 200*cos(3*t);
		V.Y += 200*sin(3*t) -500*sin(2*t);
		V.Z =0.f;
		// 여기까지는 별그리기
		monsterBullet->SetActorLocation(V);
		
		// 몬스터위치에서 총알위치를 뺀다
		V =  monsterBullet->GetActorLocation() - GetActorLocation();

		


		// 합방향벡터를 더해준다.
		
		//V*=monsterBullet->GetActorForwardVector();

		
		V.Normalize();
		const FVector Movement = V *1000.f; // 
		monsterBullet->SetVelocity(Movement);
		monsterBullet->SetLifeSpan();

	
	}
	World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);	
}
