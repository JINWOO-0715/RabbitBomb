// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTableList.h"
#include "Components/ActorComponent.h"
#include "StageManageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UStageManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStageManageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	FTimerHandle CommonMonsterSpawnTimer;
	FTimerHandle TowerMonsterSpawnTimer;
	FTimerHandle BossMonsterSpawnTimer;
	
	FTimerHandle ReturnToTile;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 데이터 테이블 Row get 탬플릿화 하면 좋겠다!
	FGameStageRow* GetGameStateRowData(int rowN =1) const;
	FCommonMonsterData* GetCommonMonsterRowData(int rowN =1) const;
	FTowerMonsterData* GetTowerMonsterRowData(int rowN=1) const;
	FBossMonsterData* GetBossMonsterRowData(int rowN=1) const;
	//FWaveType* GetWaveType(int rowN) const;

	// 스테이지 시작 함수
	UFUNCTION(BlueprintCallable)
	void StageStart(int StageNum, int WaveNum=1);
	
	// CommonMonster 스폰 함수
	UFUNCTION(BlueprintCallable)
	void SpawnCommonMonster();

	// CommonMonster 스폰 함수
	UFUNCTION(BlueprintCallable)
	void SpawnTowerMonster();

	// CommonMonster 스폰 함수
	UFUNCTION(BlueprintCallable)
	void SpawnBossMonster();

	
	// 몬스터 수 감소함수
	UFUNCTION(BlueprintCallable)
	void DecreaseDeadCommonMonster();	
	UFUNCTION(BlueprintCallable)
	void DecreaseDeadTowerMonster();
	UFUNCTION(BlueprintCallable)
	void DecreaseDeadBossMonster();	

	
	// 웨이브 시작 함수
	UFUNCTION(BlueprintCallable)
	void WaveStart();

	UFUNCTION(BlueprintCallable)
	void IsClearWave();
	
	UFUNCTION(BlueprintCallable)
	void StageClear();
	
	UFUNCTION(BlueprintCallable)
	void ReturnToTitle();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)  
	float SpawnCoolTime; 	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int NowWave;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int NowStage;			 
	
	UPROPERTY(BlueprintReadWrite)
	FWaveType NowWaveMonsterCount;

	UPROPERTY(BlueprintReadWrite)
	FWaveType MonsterDeadCount;

	
	//데이터 테이블 
	UPROPERTY(BlueprintReadWrite)
	class UDataTable* GameStageData;

	UPROPERTY(BlueprintReadWrite)
	class UDataTable* CommonMonsterData;

	UPROPERTY(BlueprintReadWrite)
	class UDataTable* TowerMonsterData;

	UPROPERTY(BlueprintReadWrite)
	class UDataTable* BossMonsterData;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> SpawnPoints;
	
	
};
