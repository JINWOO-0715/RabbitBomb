// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MonsterActor.h"
#include "TowerMonsterActor.h"
#include "CoreMinimal.h"
#include "CommonMonster.h"
#include "BossMonsterActor.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolComponent();
	

	class ACommonMonster* GetPooledCommonMonster();
	
	// class AMonsterActor* GetPooledMonster();
	//
	// class ATowerMonsterActor* GetPooledTowerMonster();
	//
	// class ABossMonsterActor* GetPooledBossMonster();
	//
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//���� ����
	void Spawn();

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ACommonMonster> MonsterSubclassOf;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int PoolSize =100;

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int BossPoolSize =3;

	TArray<ACommonMonster*> MonsterPool;

	
};
