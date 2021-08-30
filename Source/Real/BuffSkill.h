// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuffSkill.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API UBuffSkill : public UObject
{
	GENERATED_BODY()

public:
	void SetPlayerBuff(FName mSkillName);
	
};
