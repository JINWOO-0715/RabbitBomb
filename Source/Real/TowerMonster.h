// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "TowerMonster.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API ATowerMonster : public AMonster
{
	GENERATED_BODY()

	public:
	ATowerMonster();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void Mfire() override;

	void InitMonster(const FTowerMonsterData* mMonsterStat);
};
