// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"


#include "MonsterDataTable.generated.h"

USTRUCT(BlueprintType)
struct FMonsterRow : public FTableRowBase
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
};

UCLASS()
class REAL_API AMonsterDataTable : public AActor
{
	GENERATED_BODY()
	

};
