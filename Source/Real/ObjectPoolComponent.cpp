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

AMonsterActor* UObjectPoolComponent::GetPooledObject()
{
	for (AMonsterActor* PoolableActor : Pool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}

// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	if(PooledObjectSubclass !=NULL)
	{
		UWorld* const world =GetWorld();
		if(world)
		{
			for(int i =0 ; i<PoolSize;i++)
			{
				AMonsterActor* PoolableActor = GetWorld()->SpawnActor<AMonsterActor>(PooledObjectSubclass,FVector().ZeroVector,FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);
				//UE_LOG(LogTemp,Warning,TEXT("add object"));
			}
		}
	}
	// ...
	
}


// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

