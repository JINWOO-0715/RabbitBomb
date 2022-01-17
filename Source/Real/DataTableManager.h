// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "DataTableManager.generated.h"


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
	class UStaticMesh* MonsterMesh;

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
struct FDataTableManage: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* D_MonsterData;
	 	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* D_GameState;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* D_PlayerSkill;
};

UCLASS()
class REAL_API ADataTableManager : public AActor
{
	GENERATED_BODY()

};
