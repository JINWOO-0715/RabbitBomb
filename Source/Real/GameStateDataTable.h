// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"


#include "GameStateDataTable.generated.h"



USTRUCT(BlueprintType)
struct FWaveType : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int eCommomMonster;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int eTowerMonster;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int eBossMonster;



};


USTRUCT(BlueprintType)
struct FGameStateRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Stage;
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int WaveMonsterCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int WaveCount;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int,FWaveType> MonsterWave;

};

UCLASS()
class REAL_API AGameStateDataTable : public AActor
{
	GENERATED_BODY()


};
