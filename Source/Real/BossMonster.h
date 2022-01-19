// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API ABossMonster : public AMonster
{
	GENERATED_BODY()

	public:
	ABossMonster();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void Mfire();

	void InitMonster(const FBossMonsterData* mMonsterStat);
};
