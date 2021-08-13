// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletPoolComopnent.h"
#include "Engine.h"

// Sets default values for this component's properties
UBulletPoolComopnent::UBulletPoolComopnent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

ABullet* UBulletPoolComopnent::GetPooledBullet()
{
	for(ABullet* PoolableActor : Pool)
	{
		if(!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}


// Called when the game starts
void UBulletPoolComopnent::BeginPlay()
{
	Super::BeginPlay();

	if(PooledBulletSubClass !=NULL)
	{
		UWorld* const world = GetWorld();
		if(world)
		{
			for(int i = 0 ; i <Poolsize ; i++)
			{
				ABullet* PoolableActor = GetWorld()->SpawnActor<ABullet>(PooledBulletSubClass,FVector().ZeroVector,FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);
				UE_LOG(LogTemp,Warning,TEXT("add object"));
			}
		}
	}
	
}


// Called every frame
void UBulletPoolComopnent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

