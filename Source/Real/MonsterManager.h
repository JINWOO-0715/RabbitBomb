// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolComponent.h"
#include "MonsterActor.h"

#include "MonsterManager.generated.h"

UCLASS()
class REAL_API AMonsterManager : public AActor
{
	GENERATED_BODY()
	
	float GetLifeSpan();
	
	class UBoxComponent* SpawnVolume;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	UObjectPoolComponent* ObjectPooler;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	bool trigger;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	float LifeSpan = 5.0f;

	UPROPERTY(EditAnywhere,Category="Spawner")
	float SpawnCooldown  = 1.2f;

	FTimerHandle SpawnCooldownTimer;

	void Spawn();
public:	
	// Sets default values for this actor's properties
	AMonsterManager();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
