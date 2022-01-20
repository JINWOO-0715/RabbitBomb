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



void UBulletAttackPattern::TargetShot(const AActor* Target, const float BulletSpeed)
{
	// 1�� Ÿ���� ���� �߻�.

	//UWorld* const World = GetWorld();
	ARealGameModeBase* Gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = Gm->ObjectPooler->GetPooledBullet();

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
	ABullet* Bullet = Gm->ObjectPooler->GetPooledBullet();
	const AActor* Me = GetOwner();
	UWorld* const World = GetWorld();
	if (World)
	{
		for (int i = 0; i < 36; i++)
		{
			Bullet = Gm->ObjectPooler->GetPooledBullet();
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

void UBulletAttackPattern::StarShot()
{

	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	const AActor * const  Me = GetOwner();
	
	ABullet*  Bullet = gm->ObjectPooler->GetPooledBullet();
	FVector FireDir = Me->GetActorForwardVector();

	for(int t = -50;t<50;t++)
	{
		Bullet = gm->ObjectPooler->GetPooledBullet();
		Bullet->SetActive(true);
		Bullet->SetOwnerActor(Me);
	
		FVector V = Me->GetActorLocation();
		
		V.X += 500*cos(2*t) + 200*cos(3*t);
		V.Y += 200*sin(3*t) -500*sin(2*t);
		V.Z =0.f;
		
		// ��������� ���׸���
		Bullet->SetActorLocation(V);
		
		// ������ġ���� �Ѿ���ġ�� ����
		V =  Bullet->GetActorLocation() - Me->GetActorLocation();

		V.Z=0.f;
		// �չ��⺤�͸� �����ش�.
		
		//V*=monsterBullet->GetActorForwardVector();

		
		V.Normalize();
		const FVector Movement = V *1000.f; // 
		Bullet->SetVelocity(Movement);
		Bullet->SetLifeSpan();

	
	}


}

void UBulletAttackPattern::CircularsectorShot()
{

	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(3));

	AActor* Me = GetOwner();
	FVector FireDir = Me->GetActorForwardVector();
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->ObjectPooler->GetPooledBullet();

	for(int i = 0 ; i<5;i++)
	{
		if (monsterBullet && World)
		{
			monsterBullet = gm->ObjectPooler->GetPooledBullet();
			monsterBullet->SetActive(true);
			monsterBullet->SetOwnerActor(Me);
			monsterBullet->SetActorLocation(Me->GetActorLocation());
			FVector RotationVector(FireDir.X * cos(i * 0.1f) - FireDir.Y * sin(i * 0.1f),
								FireDir.X * sin(i * 0.1f) + FireDir.Y * cos(i * 0.1f), 0.f);
			RotationVector.Normalize();
		

			const FVector Movement = RotationVector * 1000.f; // 
			monsterBullet->SetVelocity(Movement);
			monsterBullet->SetLifeSpan();
		}
	}



}


void UBulletAttackPattern::OneStraightShot(FVector ForwardVector)
{
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = gm->ObjectPooler->GetPooledBullet();
	AActor* Me = GetOwner();
	
	if (World != nullptr)
	{
		const FRotator FireRotation = ForwardVector.Rotation();

		// ������ġ���
		FVector const SpawnLocation = Me->GetActorLocation(); //+ FireRotation.RotateVector(GunOffset);
		Bullet->SetOwnerActor(Me);
		Bullet->SetActorLocation(SpawnLocation);
		Bullet->SetActorRotation(FireRotation.GetInverse());
		ForwardVector.Normalize();
		const FVector Movement = ForwardVector * 1000.f; // 
		Bullet->SetVelocity(Movement);
		Bullet->SetLifeSpan();
		Bullet->SetActive(true);
	}
}

void UBulletAttackPattern::ThreeStraightShot(const FVector ForwardVector)
{
	const UWorld* const World = GetWorld();
	const ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = gm->ObjectPooler->GetPooledBullet();
	const AActor* const Me = GetOwner();
	
	if (World != nullptr)
	{
		float parameter = -0.3f;
		const FRotator FireRotation = ForwardVector.Rotation();
		for (int i = 0; i < 3; i++)
		{
			Bullet = gm->ObjectPooler->GetPooledBullet();
			if (Bullet)
			{
				Bullet->SetActive(true);
				Bullet->SetOwnerActor(Me);
				Bullet->SetActorLocation(Me->GetActorLocation());
				Bullet->SetActorRotation(FireRotation.GetInverse());

				FVector RotationVector(ForwardVector.X * cos(parameter) - ForwardVector.Y * sin(parameter),
									ForwardVector.X * sin(parameter) + ForwardVector.Y * cos(parameter), 0.f);
				RotationVector.Normalize();
				parameter += 0.3f;
				const FVector Movement = RotationVector * 1000.f; // 
				Bullet->SetVelocity(Movement);
				Bullet->SetLifeSpan();
			}
		}
	}
}

void UBulletAttackPattern::FiveStraightShot(const FVector ForwardVector)
{
	const UWorld* const World = GetWorld();
	const ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = gm->ObjectPooler->GetPooledBullet();
	const AActor* const Me = GetOwner();
	
	if (World != nullptr)
	{
		float parameter = -0.4f;
		const FRotator FireRotation = ForwardVector.Rotation();
		for (int i = 0; i < 5; i++)
		{
			Bullet = gm->ObjectPooler->GetPooledBullet();
			if (Bullet)
			{
				Bullet->SetActive(true);
				Bullet->SetOwnerActor(Me);
				Bullet->SetActorLocation(Me->GetActorLocation());
				Bullet->SetActorRotation(FireRotation.GetInverse());

				FVector RotationVector(ForwardVector.X * cos(parameter) - ForwardVector.Y * sin(parameter),
									ForwardVector.X * sin(parameter) + ForwardVector.Y * cos(parameter), 0.f);
				RotationVector.Normalize();
				parameter += 0.2f;
				const FVector Movement = RotationVector * 1000.f; // 
				Bullet->SetVelocity(Movement);
				Bullet->SetLifeSpan();
			}
		}
	}
}

void UBulletAttackPattern::SevenStraightShot(const FVector ForwardVector)
{
	const UWorld* const World = GetWorld();
	const ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* Bullet = gm->ObjectPooler->GetPooledBullet();
	const AActor* const Me = GetOwner();
	
	if (World != nullptr)
	{
		float parameter = -0.6f;
		const FRotator FireRotation = ForwardVector.Rotation();
		for (int i = 0; i < 7; i++)
		{
			Bullet = gm->ObjectPooler->GetPooledBullet();
			if (Bullet)
			{
				Bullet->SetActive(true);
				Bullet->SetOwnerActor(Me);
				Bullet->SetActorLocation(Me->GetActorLocation());
				Bullet->SetActorRotation(FireRotation.GetInverse());

				FVector RotationVector(ForwardVector.X * cos(parameter) - ForwardVector.Y * sin(parameter),
									ForwardVector.X * sin(parameter) + ForwardVector.Y * cos(parameter), 0.f);
				RotationVector.Normalize();
				parameter += 0.2f;
				const FVector Movement = RotationVector * 1000.f; // 
				Bullet->SetVelocity(Movement);
				Bullet->SetLifeSpan();
			}
		}
	}
}

void UBulletAttackPattern::FireStraightRandom()
{
	const AActor* Me = GetOwner();
	float parameter = -0.5f;
	FVector FireDir =Me->GetActorForwardVector();
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	ABullet* monsterBullet = gm->ObjectPooler->GetPooledBullet();
	
	for (int i = 0; i < 10; i++)
	{

		if (monsterBullet && World)
		{
			monsterBullet = gm->ObjectPooler->GetPooledBullet();
			monsterBullet->SetActive(true);
			monsterBullet->SetOwnerActor(Me);
			monsterBullet->SetActorLocation(Me->GetActorLocation());
			FVector RotationVector(FireDir.X * cos(parameter) - FireDir.Y * sin(parameter),
								FireDir.X * sin(parameter) + FireDir.Y * cos(parameter), 0.f);
			RotationVector.Normalize();
			parameter += 0.1f;
			const FVector Movement = RotationVector * 1000.f; // 
			monsterBullet->SetVelocity(Movement);
			monsterBullet->SetLifeSpan();
						
		}
				
	}
}

