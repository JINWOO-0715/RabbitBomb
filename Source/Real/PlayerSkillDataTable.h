// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

#include "PlayerSkillDataTable.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSkillRow: public FTableRowBase
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
	float DecreaseCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int,float> SkillLevelMap;
};

UCLASS()
class REAL_API APlayerSkillDataTable : public AActor
{
	GENERATED_BODY()

};
