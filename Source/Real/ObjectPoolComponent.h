// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MonsterActor.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolComponent();
	
	AMonsterActor* GetPooledMonster();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//몬스터 스폰
	void Spawn();

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class AMonsterActor> PooledMonsterSubclass;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int PoolSize =100;

	TArray<AMonsterActor*> Pool;
};
