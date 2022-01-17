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

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void Mfire() override;


	UFUNCTION(BlueprintCallable)
	void MoveToTarget();
	
	// 움직이는 함수 

};
