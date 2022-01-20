// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"

#include "Engine.h"


// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

ACommonMonster* UObjectPoolComponent::GetPooledCommonMonster()
{
	for (ACommonMonster* PoolableActor : CommonMonstersPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}

ATowerMonster* UObjectPoolComponent::GetPooledTowerMonster()
{
	for (ATowerMonster* PoolableActor : TowerMonstersPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}


ABossMonster* UObjectPoolComponent::GetPooledBossMonster()
{
	for (ABossMonster* PoolableActor : BossMonstersPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}

ABullet* UObjectPoolComponent::GetPooledBullet()
{
	for (ABullet* PoolableActor : BulletsPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;


}

AItemActor* UObjectPoolComponent::GetPooledItemActor()
{
	for (AItemActor* PoolableActor : ItemPool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;


}

ACoinItem* UObjectPoolComponent::GetPooledCoinItemActor()
{
	for (ACoinItem* PoolableActor : CoinPool)
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

	CommonMonsterSpawn();
	TowerMonsterSpawn();
	BossMonsterSpawn();
	BulletSpawn();
	ItemSpawn();
}

void UObjectPoolComponent::CommonMonsterSpawn()
{
	if (CommonMonsterSubclassOf != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				ACommonMonster* CommonMonster = GetWorld()->SpawnActor<ACommonMonster>(
					CommonMonsterSubclassOf, FVector().ZeroVector, FRotator().ZeroRotator);
				CommonMonster->SetActive(false);
				CommonMonstersPool.Add(CommonMonster);
			}
		}
	}
}

void UObjectPoolComponent::TowerMonsterSpawn()
{
	if (TowerMonsterSubclassOf != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				ATowerMonster* CommonMonster = GetWorld()->SpawnActor<ATowerMonster>(
					TowerMonsterSubclassOf, FVector().ZeroVector, FRotator().ZeroRotator);
				CommonMonster->SetActive(false);
				TowerMonstersPool.Add(CommonMonster);
			}
		}
	}
}

void UObjectPoolComponent::BossMonsterSpawn()
{
	if (BossMonsterSubclassOf != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				ABossMonster* CommonMonster = GetWorld()->SpawnActor<ABossMonster>(
					BossMonsterSubclassOf, FVector().ZeroVector, FRotator().ZeroRotator);
				CommonMonster->SetActive(false);
				BossMonstersPool.Add(CommonMonster);
			}
		}
	}
}

void UObjectPoolComponent::BulletSpawn()
{
	if (BulletSubclassOf != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < BulletPoolSize; i++)
			{
				ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(
					BulletSubclassOf, FVector().ZeroVector, FRotator().ZeroRotator);
				Bullet->SetActive(false);
				BulletsPool.Add(Bullet);
			}
		}
	}
}

void UObjectPoolComponent::ItemSpawn()
{
	if (ItemSubclassOf != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				AItemActor* ItemActor = GetWorld()->SpawnActor<AItemActor>(
					ItemSubclassOf, FVector().ZeroVector, FRotator().ZeroRotator);
				ItemActor->SetActive(false);
				ItemPool.Add(ItemActor);
			}
		}
	}
	if (CoinSubclassOf != NULL)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				ACoinItem* CoinItem = GetWorld()->SpawnActor<ACoinItem>(
					CoinSubclassOf, FVector().ZeroVector, FRotator().ZeroRotator);
				CoinItem->SetActive(false);
				CoinPool.Add(CoinItem);
			}
		}
	}
}

// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	// if (PooledMonsterSubclass != NULL)
	// {
	// 	UWorld* const world = GetWorld();
	// 	if (world)
	// 	{
	// 		for (int i = 0; i < PoolSize; i++)
	// 		{
	// 			AMonsterActor* PoolableActor = GetWorld()->SpawnActor<AMonsterActor>(
	// 				PooledMonsterSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
	// 			PoolableActor->SetActive(false);
	// 			CommonMonsterPool.Add(PoolableActor);
	// 			//UE_LOG(LogTemp,Warning,TEXT("add object"));
	// 		}
	// 	}
	// }
	// ...
}


// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
