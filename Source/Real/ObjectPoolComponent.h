// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "CommonMonster.h"
#include "BossMonster.h"
#include "TowerMonster.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	// ������
	UObjectPoolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Ǯ�� ���� ��ü ����
	UFUNCTION(BlueprintCallable)
	void Spawn();

	// Spawn�Լ�
	UFUNCTION(BlueprintCallable)
	void CommonMonsterSpawn();
	UFUNCTION(BlueprintCallable)
	void TowerMonsterSpawn();
	UFUNCTION(BlueprintCallable)
	void BossMonsterSpawn();

	// Getter�Լ�
	class ACommonMonster* GetPooledCommonMonster();
	class ATowerMonster* GetPooledTowerMonster();
	class ABossMonster* GetPooledBossMonster();
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ACommonMonster> CommonMonsterSubclassOf;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ATowerMonster> TowerMonsterSubclassOf;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ABossMonster> BossMonsterSubclassOf;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int PoolSize =100;

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int BossPoolSize =3;

	UPROPERTY(BlueprintReadWrite);
	TArray<ACommonMonster*> CommonMonstersPool;
	
	UPROPERTY(BlueprintReadWrite);
	TArray<ATowerMonster*> TowerMonstersPool;
	
	UPROPERTY(BlueprintReadWrite);
	TArray<ABossMonster*> BossMonstersPool;

	
};
