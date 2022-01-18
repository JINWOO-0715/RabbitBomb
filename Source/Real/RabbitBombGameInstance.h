// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTableList.h"
#include "Engine/GameInstance.h"

// #include  �������� �Ŵ��� 
#include "RabbitBombGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API URabbitBombGameInstance : public UGameInstance
{
	GENERATED_BODY()

	// �������� �Ŵ��� ����.  -> ����->���� �Ѿ��, ���� ����(DT���� ������ �ܾ����)
	// �� �������� �ʱ�ȭ ���ִ¾�.
	// ������ ���̺��� ������ �ܾ���°� 
	//
	//
	// UI�Ŵ��� ����
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
