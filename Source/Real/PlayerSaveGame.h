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
	int FireRatelevel = 1;

	// ??????
	UPROPERTY(EditAnywhere)
	float FireRate = 1.f;

	UPROPERTY()
	int MoveSpeedlevel = 1;
	// ?????? ?????
	UPROPERTY()
	float MoveSpeed;

	// ?????
	UPROPERTY()
	float BulletPower = 50.f;
	UPROPERTY()
	int BulletPowerlevel = 1;

	//HP
	UPROPERTY()
	float MaxHP = 100.f;
	UPROPERTY()
	int MaxHPlevel = 1;

	UPROPERTY()
	int PlayerCoin = 100;

	UPROPERTY()
	int PlayerStage =1;;

	UPROPERTY()
	bool PlayerStorySaw =false;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName; // Save game data file name

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex; // Save game data file index


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName SaveName;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	float SaveFloat;


	
};
