// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "CommonMonster.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API ACommonMonster : public AMonster
{
	GENERATED_BODY()

	public:
	ACommonMonster();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void Mfire();

	// 움직이는 함수
	UFUNCTION(BlueprintCallable)
	void MoveToTarget();
	
	void InitMonster(const FCommonMonsterData* mMonsterStat);
	
	//void InitMonster( const FCommonMonsterData* mMonsterStat );


 

};
