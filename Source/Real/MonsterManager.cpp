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
	//데이터 테이블.
	
}

// Called when the game starts or when spawned
void AMonsterManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
}

void AMonsterManager::Spawn()
{
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	AMonsterActor* Monster = gm->MonsterPooler->GetPooledMonster();
		
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
		return;
	}

	Monster->SetActorLocation(GetActorLocation());
	//PoolableActor->SetLifeSpan(LifeSpan);
	Monster->InitMonster(MonsterNum);
	Monster->SetActive(true);

	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, true);
	UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));

}

// Called every frame
void AMonsterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
