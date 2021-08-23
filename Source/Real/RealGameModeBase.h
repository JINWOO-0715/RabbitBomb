// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"
#include "ObjectPoolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	
	//타이머 핸들
	FTimerHandle TimerHandle_ShotTimerExpired;

protected:
	virtual void BeginPlay() override;
public:
	ARealGameModeBase();

	
	//총알 담기
	UPROPERTY(EditAnywhere,Category="Spawner")
	UBulletPoolComopnent* BulletPooler;

	// 몬스터 담기 
	UPROPERTY(EditAnywhere,Category="Spawnere")
	UObjectPoolComponent* MonsterPooler;
	
	
	
	// 플레이어 오른쪽아래 위젯
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerRightWidgetClass;

	
	UPROPERTY(VisibleInstanceOnly)
	class URightWidget* PlayerRightWidget;
};
