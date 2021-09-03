// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"
#include "ObjectPoolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerSkillDataTable.h"
#include "ItemPoolComponent.h"
#include "MonsterDataTable.h"
#include "MainPawn.h"

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
	float StartTime =0.0f;

protected:
	virtual void BeginPlay() override;
	
public:
	ARealGameModeBase();
	
	//�޽�

	
	virtual void Tick(float DeltaTime) override;
	
	// ���� ���� �ֱ�
	UPROPERTY(EditAnywhere,Category="Spawner")
	float MonsterSpawnCoolTime =2.0f;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterSpawnNum =2;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterType =2;

	
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

	FORCEINLINE	float GetPlayTime() const {return StartTime;};
};
