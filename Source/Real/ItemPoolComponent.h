// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "Components/ActorComponent.h"
#include "ItemPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UItemPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemPoolComponent();

	// 들어간거 가져오는거
	class AItemActor* GetPooledUItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Spawn();

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class AItemActor> PooledItemSubClass;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int Poolsize = 100;

	TArray<AItemActor*> Pool;
	
		
};
