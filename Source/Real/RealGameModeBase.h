// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"
#include "ObjectPoolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerSkillDataTable.h"
#include "ItemPoolComponent.h"
#include "GameStateDataTable.h"
#include "MonsterDataTable.h"

#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "MainPawn.h"
#include "PlayerSaveGame.h"
#include "BossMonsterActor.h"
#include "ItemActor.h"
#include "ChooseSkillWidget.h"
#include "GameStateDataTable.h"
#include "MonsterManager.h"
#include "RealGameModeBase.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ARealGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Spawner")
	bool trigger;

	void MonsterSpawn();
	
	//Ÿ�̸� �ڵ�
	FTimerHandle MonsterSpawnTimer;

	class UDataTable* MonsterData;
	class UDataTable* PlayerSkillData;
	class UDataTable* GameStageData;

	
	class AMonsterManager* WorldMonsterManger;

	FWaveType NowMosterCount; 
	 
	// FWaveType WaveMonsterCount;
	//float StartTime =0.0f;

protected:
	virtual void BeginPlay() override;
	
public:
	ARealGameModeBase();


	void SetMonsterManager(AMonsterManager* mMonsterManager);
		
	void CheckStage();
	
	//�޽�

	void DecreaseCommomMonsterCount();
	
	virtual void Tick(float DeltaTime) override;

	
	FGameStateRow* GoalGameStage;
	int NowStage = 1;
	int NowWave	= 1;
	
	// ���� ���� �ֱ�
	UPROPERTY(EditAnywhere,Category="Spawner")
	float MonsterSpawnCoolTime =2.0f;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterSpawnNum =2;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterType =2;

	UPROPERTY(EditAnywhere,Category="Spawner")
	float CheatTime =0.f;

	
	UPROPERTY(EditAnywhere,Category="Spawner")
	int SpawnRangeMin =800;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	int SpawnRangeMax =1500;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	float SpawnCoolTimeRandomMin =0.f;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	float SpawnCoolTimeRandomMax =2.0f;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	int SpawnMonsterRandomNumMin=0;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int SpawnMonsterRandomNumMax=5;
	
	
	//�Ѿ� ���
	UPROPERTY(EditAnywhere,Category="Spawner")
		class 	UBulletPoolComopnent* BulletPooler;

	// ���� ��� 
	UPROPERTY(EditAnywhere,Category="Spawner")
		class UObjectPoolComponent* MonsterPooler;

	UPROPERTY(EditAnywhere,Category="Spawner")
		class UItemPoolComponent* ItemPooler;


	//���� ������ �ʱ�ȭ
	FMonsterRow* GetMonsterRowData(int rowN);
	FMonsterRow* GetMonsterRowData(FName mSkillName);

	//�÷��̾� ��ų ��������
	FPlayerSkillRow* GetPlayerSkillRowDataToNum(int rowN);
	FPlayerSkillRow* GetPlayerSkillRowDataToNum(FName mSkillName);
	
	//�������� ���� ��������
	FGameStateRow* GetGameStateRowData(int rowN);
	
	// //�÷��̾� ��ų �ʱ�ȭ
	// FPlayerSkillRow* GetPlayerSkillRowDataToName(FName mSkillName);

	
	// �÷��̾� �����ʾƷ� ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerRightWidgetClass;

	// �÷��̾� �����ʾƷ� ����
	UPROPERTY(VisibleInstanceOnly)
	class URightWidget* PlayerRightWidget;

	// �÷��̾� ��ų����
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerSkillChooseClass;

	// �÷��̾� ��ų���� ����
	UPROPERTY(VisibleInstanceOnly)
	class UChooseSkillWidget* PlayerSkillChooseWidget;

	//FORCEINLINE	float GetPlayTime() const {return StartTime;};

	UFUNCTION(BlueprintCallable)
	void Save();

	UFUNCTION(BlueprintCallable)
	void Load();

	int GetGoalCommonMonsterCount();
	
	
	int GetGoalWave();


	//
	// void UpCommomMonsterCount();
	// void UpTowerMonsterCount();
	// void UpBossMonsterCount();
	//
	// // void SetStage(int mStage);
	//
	// FORCEINLINE int GetStage() const { return NowStage;};

	// bool isSpawnAble();
};



