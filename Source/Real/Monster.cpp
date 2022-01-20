// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "RealGameModeBase.h"
#include "CoinItem.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �޽�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MonsterMeshComponent;
	
	// �浹����
	SetActorEnableCollision(false);
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonsterMeshComponent->SetCollisionProfileName("Monster");

	// �±� ����
	Tags.Add("Monster");

	
	//��������
	AttackPatternComponent = CreateDefaultSubobject<UBulletAttackPattern>(TEXT("AttackPatternComponent"));

	// ���� �⺻����.
	Active =false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	//

}



float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& MovieSceneBlends, AController* EventInstigator,
	AActor* DamageCauser)
{
	//float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float Damage = DamageAmount;
	MonsterHP -= Damage;
	//ChangeHitedMTTimer();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	
	if (MonsterHP < 0.f)
	{
		UGameplayStatics::PlaySound2D(this, gm->MonsterDeadSound );
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->DeadParticle, GetActorLocation(),FRotator(0.f,0.f,0.f),FVector(3.f,3.f,3.f));
		
		AMainPawn* player=Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		//player->PlayerScoreWidget->DereaseMonsterText();
		
		int rand = FMath::RandRange(0, 1);
		
		if (rand == 0)
		{
			AItemActor* Item = gm->ObjectPooler->GetPooledItemActor();
			Item->SetActorLocation(GetActorLocation());
			Item->SetActive(true);
		}
		
		rand = FMath::RandRange(0, 1);
		
		if (rand == 0)
		{
			
			ACoinItem* Coin = gm->ObjectPooler->GetPooledCoinItemActor();
			Coin->SetActorLocation(GetActorLocation()+FVector(50.f,0.f,0.f));
			Coin->SetActive(true);
		}
		//��ġ���� ȹ�� Ȯ�� 40%
		SetActive(false);
	
		if(ActorHasTag(FName("CommonMonster")))
		{
			gm->StageManageComponent->DecreaseDeadCommonMonster();
		}
		else if(ActorHasTag(FName("TowerMonster")))
		{
			gm->StageManageComponent->DecreaseDeadTowerMonster();
		}
		else if(ActorHasTag(FName("BossMonster")))
		{
			gm->StageManageComponent->DecreaseDeadBossMonster();
		}
		//;
	}
	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->HitedParticle, GetActorLocation(),FRotator(0.f,0.f,0.f),FVector(3.f,3.f,3.f));
		UGameplayStatics::PlaySound2D(this, gm->MonsterHitSound);
	}
	return Damage;

}


void AMonster::SetActive(bool InActive)
{
	Active=InActive;
	// �浹 off
	SetActorEnableCollision(InActive);

	//�����
	SetActorHiddenInGame(!InActive);

	//�޽� 
	MonsterMeshComponent->SetActive(InActive);

	//ƽ����
	SetActorTickEnabled(InActive);

	bCanFire=InActive;
	
	if(InActive)
	{
		GetWorldTimerManager().SetTimer(AttackTimer, this
							, &AMonster::ShotTimerExpired, MonsterStat.FireRate,InActive);
		//UE_LOG(LogTemp, Warning,TEXT("Timer is Sucess %f" ),MonsterStat.FireRate);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(AttackTimer);
	}

	
		
		
}

// Called every frame
// void AMonster::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }

bool AMonster::IsActive()
{
	return Active;
}

void AMonster::ShotTimerExpired()
{
	
	bCanFire = true;
	//UE_LOG(LogTemp, Warning,TEXT("ShotTimerExpired is Sucess %f" ),bCanFire);
}

