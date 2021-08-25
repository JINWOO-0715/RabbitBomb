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
	
	//타이머 핸들
	FTimerHandle MonsterSpawnTimer;

	// 데이터 테이블
	class UDataTable* LevelUpDataTable;
protected:
	virtual void BeginPlay() override;
public:
	ARealGameModeBase();
	
	
	
	// 몬스터 생성 주기
	UPROPERTY(EditAnywhere,Category="Spawner")
	float MonsterSpawnCoolTime =2.0f;

	UPROPERTY(EditAnywhere,Category="Spawner")
	int MonsterNum =2;
	
	//총알 담기
	UPROPERTY(EditAnywhere,Category="Spawner")
	UBulletPoolComopnent* BulletPooler;

	// 몬스터 담기 
	UPROPERTY(EditAnywhere,Category="Spawnere")
	UObjectPoolComponent* MonsterPooler;

	//몬스터 데이터 초기화
	FMonsterRow* GetMonsterRowData(int rowN);
	
	//몬스터 데이터 
	TArray<FMonsterRow*> MonsterRow;
	
	// 플레이어 오른쪽아래 위젯
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerRightWidgetClass;

	// 플레이어 오른쪽아래 위젯
	UPROPERTY(VisibleInstanceOnly)
	class URightWidget* PlayerRightWidget;
};
