// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "TowerMonsterActor.h"

// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

AMonsterActor* UObjectPoolComponent::GetPooledMonster()
{
	for (AMonsterActor* PoolableActor : CommonMonsterPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}

ATowerMonsterActor* UObjectPoolComponent::GetPooledTowerMonster()
{
	for (ATowerMonsterActor* PoolableActor : TowerMonsterPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;

}

ABossMonsterActor* UObjectPoolComponent::GetPooledBossMonster()
{
	for (ABossMonsterActor* PoolableActor : BossMonsterPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}

void UObjectPoolComponent::Spawn()
{
	//Super::BeginPlay();

	if (PooledMonsterSubclass != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				AMonsterActor* PoolableActor = GetWorld()->SpawnActor<AMonsterActor>(
					PooledMonsterSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				CommonMonsterPool.Add(PoolableActor);

				ATowerMonsterActor* TowerPoolableActor = GetWorld()->SpawnActor<ATowerMonsterActor>(
					PooledTowerMonsterSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				TowerPoolableActor->SetActive(false);
				TowerMonsterPool.Add(TowerPoolableActor);

				UE_LOG(LogTemp, Warning, TEXT("add object"));
			}
			for (int i = 0; i < BossPoolSize; i++)
			{
				ABossMonsterActor* BossPoolableActor = GetWorld()->SpawnActor<ABossMonsterActor>(
					PooledBossMonsterSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				BossPoolableActor->SetActive(false);
				BossMonsterPool.Add(BossPoolableActor);
			}
		}
	}
}

// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	if (PooledMonsterSubclass != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				AMonsterActor* PoolableActor = GetWorld()->SpawnActor<AMonsterActor>(
					PooledMonsterSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				CommonMonsterPool.Add(PoolableActor);
				//UE_LOG(LogTemp,Warning,TEXT("add object"));
			}
		}
	}
	// ...
}


// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
