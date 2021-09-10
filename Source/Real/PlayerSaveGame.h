// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()


	public:
	UPlayerSaveGame();

	UPROPERTY()
	int level =1;
	
	// ���ݼӵ�
	UPROPERTY(EditAnywhere)
	float FireRate = 1.f;

	// �̵��ӵ� ���ǵ�
	UPROPERTY()
	float MoveSpeed;
	
	// ���ݷ�
	UPROPERTY()
	float BulletPower=50.f;
	//HP
	UPROPERTY()
	float MaxHP =100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;		// Save game data file name

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex;		// Save game data file index



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName SaveName;
	


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	float SaveFloat;
};
