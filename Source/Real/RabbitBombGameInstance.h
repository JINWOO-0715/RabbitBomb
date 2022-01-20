// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTableList.h"
#include "Engine/GameInstance.h"

// #include  스테이지 매니져 
#include "RabbitBombGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API URabbitBombGameInstance : public UGameInstance
{
	GENERATED_BODY()

	
	public:
	int NowStage;

	
	
	int PlayerFireRateLevel =1;
	int PlayerPowerLevel =1;
	int PlayerSpeedLevel =1;
	int PlayerHPLevel=1;

	int PlayerHasCoin =100000;

	int MonsterCount=0;

	bool isStroySaw=false;
	
};
