// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"
#include "ObjectPoolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerSkillDataTable.h"
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

	class UDataTable* MonsterData;
	class UDataTable* PlayerSkillData;

protected:
	virtual void BeginPlay() override;
	
public:
	ARealGameModeBase();
	
	virtual void Tick(float DeltaTime) override;
	
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

	//�÷��̾� ��ų �ʱ�ȭ
	FPlayerSkillRow* GetPlayerSkillRowData(int rowN);
	

	
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
};
