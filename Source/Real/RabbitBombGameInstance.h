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

	// 스테이지 매니져 생성.  -> 레벨->레벨 넘어갈때, 몬스터 생성(DT에서 데이터 긁어오기)
	// 및 스테이지 초기화 해주는애.
	// 데이터 테이블에서 데이터 긁어오는건 
	//
	//
	// UI매니져 생성
	// get
	
	public:
	int NowStage;

	
	
	int PlayerFireRateLevel =1;
	int PlayerPowerLevel =1;
	int PlayerSpeedLevel =1;
	int PlayerHPLevel=1;

	int PlayerHasCoin =100000;

	int MonsterCount=0;
	int NowWave=1;
	int GoalWave=1;

	bool isStroySaw=false;
	
};
