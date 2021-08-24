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
	
	//Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle_ShotTimerExpired;

	// ������ ���̺�
	class UDataTable* LevelUpDataTable;
protected:
	virtual void BeginPlay() override;
public:
	ARealGameModeBase();
	

	TArray<FMonsterRow*> MonsterRow;
	
	//�Ѿ� ���
	UPROPERTY(EditAnywhere,Category="Spawner")
	UBulletPoolComopnent* BulletPooler;

	// ���� ��� 
	UPROPERTY(EditAnywhere,Category="Spawnere")
	UObjectPoolComponent* MonsterPooler;

	FMonsterRow* GetMonsterRowData(int rowN);
	
	
	// �÷��̾� �����ʾƷ� ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerRightWidgetClass;

	
	UPROPERTY(VisibleInstanceOnly)
	class URightWidget* PlayerRightWidget;
};
