// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	float PlayerFireRateLevel;

	float PlayerPowerLevel;
	float PlayerSpeedLevel;
	float PlayerHPLevel;

	int PlayerHasCoin;
	
};
