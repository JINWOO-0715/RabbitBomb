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

	FTimerHandle SpawnTimer;
	FTimerHandle ReturnToTile;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ������ ���̺� Row get
	FGameStageRow* GetGameStateRowData(int rowN) const;
	FCommonMonsterData* GetCommonMonsterRowData(int rowN) const;
	//FWaveType* GetWaveType(int rowN) const;

	// �������� ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void StageStart(int StageNum, int WaveNum=1);
	
	// CommonMonster ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void SpawnCommonMonster();

	// CommonMonster ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void SpawnTowerMonster();

	// CommonMonster ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void SpawnBossMonster();

	
	// ���� �� �����Լ�
	UFUNCTION(BlueprintCallable)
	void DecreaseDeadCommonMonster();	
	
	// ���̺� ���� �Լ�
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

	
	//������ ���̺� 
	UPROPERTY(BlueprintReadWrite)
	class UDataTable* GameStageData;

	UPROPERTY(BlueprintReadWrite)
	class UDataTable* CommonMonsterData;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> SpawnPoints;
	
	
};
