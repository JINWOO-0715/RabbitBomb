// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPoolComponent.h"

// Sets default values for this component's properties
UItemPoolComponent::UItemPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UItemPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
AItemActor* UItemPoolComponent::GetPooledUItem()
{
	for(AItemActor* PoolableActor : Pool)
	{
		if(!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}


void UItemPoolComponent::Spawn()
{
	//Super::BeginPlay();

	if(PooledItemSubClass !=NULL)
	{
		UWorld* const world = GetWorld();
		if(world)
		{
			for(int i = 0 ; i <Poolsize ; i++)
			{
				AItemActor* PoolableActor = GetWorld()->SpawnActor<AItemActor>(PooledItemSubClass,FVector().ZeroVector,FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);
				UE_LOG(LogTemp,Warning,TEXT("add object"));
			}
		}
	}
	
}
// Called every frame
void UItemPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

