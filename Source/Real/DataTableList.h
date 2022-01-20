// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <utility>

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "DataTableList.generated.h"


USTRUCT(BlueprintType)
struct FPSkillData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SKillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActiveSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IncreaseCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int,float> SkillLevelMap;
};

USTRUCT(BlueprintType)
struct FStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MonsterHP;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lifespan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSpeed = 500.0f;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletLifeSpan = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletPower = 5.0f;
};

USTRUCT(BlueprintType)
struct FCommonMonsterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* MonsterMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatData Stat;
};

USTRUCT(BlueprintType)
struct FTowerMonsterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* MonsterMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatData Stat;
};

USTRUCT(BlueprintType)
struct FBossMonsterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* MonsterMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FStatData Stat;
};
USTRUCT(BlueprintType)
struct FWaveType : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CommonMonsterSpawnCount;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TowerMonsterSpawnCount;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BossMonsterSpawnCount;



};

USTRUCT(BlueprintType)
struct FGameStageRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stage=1;
   
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CommonMonsterType=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TowerMonsterType=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BossMonsterType=1;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int,FWaveType> MonsterWave;

    

};

USTRUCT(BlueprintType)
struct FDataTableManage: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()


	// list??
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* D_CommonMonsterData;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* D_PlayerSkill;

	// 시도1 연산자 오버로딩 but 값이 안넘어감
	// FDataTableManage& operator =( const FDataTableManage* ref) 
	// {
	// 	FDataTableManage TmpDataTableManage;
	// 	TmpDataTableManage.D_CommonMonsterData=ref->D_CommonMonsterData;
	// 	
	// 	TmpDataTableManage.D_PlayerSkill=ref->D_PlayerSkill;
	//
	// 	return *this;
	// }

	// 시도2 Copy함수 만들기??
	
	

};

UCLASS()
class REAL_API ADataTableManager : public AActor
{
	GENERATED_BODY()

};
