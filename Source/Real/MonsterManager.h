// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateDataTable.h"
#include "MonsterManager.generated.h"

UCLASS()
class REAL_API AMonsterManager : public AActor
{
	GENERATED_BODY()
	
	//float GetLifeSpan();
	
	class UBoxComponent* SpawnVolume;

	// UPROPERTY(EditAnywhere,Category="Spawner")
	// UObjectPoolComponent* ObjectPooler;

	UPROPERTY(EditAnywhere,Category="Spawner")
	float SpawnCooldown  = 1.2f;
	int NowWave =1;
	
	
	UPROPERTY(EditAnywhere,Category="Spawner", Meta = (MakeEditWidget = true))
	FVector SpawnLocation[9];
	
	FTimerHandle SpawnCooldownTimer;


	bool isActive;
	void Spawn();

	FWaveType NowSpawnMosterCount;

	
public:	
	// Sets default values for this actor's properties
	AMonsterManager();

	void ResetCount();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
