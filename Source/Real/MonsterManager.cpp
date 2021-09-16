// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterManager.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "Components/BoxComponent.h"
#include "RealGameModeBase.h"

#include "GameFramework/Pawn.h"

// Sets default values
AMonsterManager::AMonsterManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnVolume"));

	RootComponent = SpawnVolume;

	
	//ObjectPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPoller"));
	//
	//������ ���̺�.
	
}

void AMonsterManager::ResetCount()
{
	NowSpawnMosterCount.eCommomMonster =0;
	NowSpawnMosterCount.eBossMonster =0;
	NowSpawnMosterCount.eTowerMonster =0;
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown);
}


// Called when the game starts or when spawned
void AMonsterManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown);
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	gm->SetMonsterManager(this);
	
}


// �����Ҽ��ְ� ������ �ʰ� �˾ƾ��ϴ°� �ƴϳ�!

void AMonsterManager::Spawn()
{
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	AMonsterActor* Monster = gm->MonsterPooler->GetPooledMonster();


	// ���Ͱ� ���׾���

	// ���������� �ø��� ���� �ø��� üũ�Ѵ�
	// ���Ͱ� �� ��ȯ�ƴ��� Ȯ���Ѵ�.

	// ��ȯ�ؾ��Ҷ� �̰� Ű�� �ؾ��Ҷ� = ���������� �Ѿ��!
	// �ٵǸ� �����µ�

	// ��ǥ��ŭ 
	if(NowSpawnMosterCount.eCommomMonster < gm->GetGoalCommonMonsterCount())
	{
		
		if (Monster == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
			return;
		}
		// ���� ��ġ
		Monster->SetActorLocation(SpawnLocation[0]);
		//���� ����
		Monster->InitMonster(1);
		// Ȱ��ȭ ����
		Monster->SetActive(true);
		UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));
		//��ǥ��ġ ++
		NowSpawnMosterCount.eCommomMonster++;
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::FromInt(NowSpawnMosterCount.eCommomMonster));
	}
	else
	{
		//��������.
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("PULL"));
	
	}


		

}

// Called every frame
void AMonsterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
