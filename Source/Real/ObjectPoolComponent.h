// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "CommonMonster.h"
#include "BossMonster.h"
#include "Bullet.h"
#include "ItemActor.h"
#include "CoinItem.h"


#include "TowerMonster.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	// 생성자
	UObjectPoolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//풀링 전부 객체 스폰
	UFUNCTION(BlueprintCallable)
	void Spawn();

	// Spawn함수
	UFUNCTION(BlueprintCallable)
	void CommonMonsterSpawn();
	UFUNCTION(BlueprintCallable)
	void TowerMonsterSpawn();
	UFUNCTION(BlueprintCallable)
	void BossMonsterSpawn();
	UFUNCTION(BlueprintCallable)
	void BulletSpawn();
	UFUNCTION(BlueprintCallable)
	void ItemSpawn();

	// Getter함수
	class ACommonMonster* GetPooledCommonMonster();
	class ATowerMonster* GetPooledTowerMonster();
	class ABossMonster* GetPooledBossMonster();
	class ABullet* GetPooledBullet();
	class AItemActor* GetPooledItemActor();
	class ACoinItem* GetPooledCoinItemActor();
	
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ACommonMonster> CommonMonsterSubclassOf;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ATowerMonster> TowerMonsterSubclassOf;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ABossMonster> BossMonsterSubclassOf;

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ABullet> BulletSubclassOf;

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class AItemActor> ItemSubclassOf;

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ACoinItem> CoinSubclassOf;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int PoolSize =100;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int BulletPoolSize =100;

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int BossPoolSize =3;

	UPROPERTY(BlueprintReadWrite);
	TArray<ACommonMonster*> CommonMonstersPool;
	
	UPROPERTY(BlueprintReadWrite);
	TArray<ATowerMonster*> TowerMonstersPool;
	
	UPROPERTY(BlueprintReadWrite);
	TArray<ABossMonster*> BossMonstersPool;

	UPROPERTY(BlueprintReadWrite);
	TArray<ABullet*> BulletsPool;
	
	UPROPERTY(BlueprintReadWrite);
	TArray<AItemActor*> ItemPool;
	
	UPROPERTY(BlueprintReadWrite);
	TArray<ACoinItem*> CoinPool;

	// BulletMesh(몬스터 플레이어에 따라 바뀜)
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	class UStaticMesh* MonsterBulletMesh;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler");
	class UStaticMesh* PlayeruBulletMesh;

};
