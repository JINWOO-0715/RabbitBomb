// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"
#include "ObjectPoolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MonsterDataTable.h"

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

	// ������ ���̺�
	class UDataTable* LevelUpDataTable;
protected:
	virtual void BeginPlay() override;
public:
	ARealGameModeBase();
	
	
	
	// ���� ���� �ֱ�
	UPROPERTY(EditAnywhere,Category="Spawner")
	float MonsterSpawnCoolTime =2.0f;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterNum =2;
	
	//�Ѿ� ���
	UPROPERTY(EditAnywhere,Category="Spawner")
	UBulletPoolComopnent* BulletPooler;

	// ���� ��� 
	UPROPERTY(EditAnywhere,Category="Spawnere")
	UObjectPoolComponent* MonsterPooler;

	//���� ������ �ʱ�ȭ
	FMonsterRow* GetMonsterRowData(int rowN);
	
	//���� ������ 
	TArray<FMonsterRow*> MonsterRow;
	
	// �÷��̾� �����ʾƷ� ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerRightWidgetClass;

	// �÷��̾� �����ʾƷ� ����
	UPROPERTY(VisibleInstanceOnly)
	class URightWidget* PlayerRightWidget;
};
