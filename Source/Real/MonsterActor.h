// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterActor.generated.h"

UCLASS()
class REAL_API AMonsterActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MonseterMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MonsterHP = 100.f;

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;



	// float LifeSpan = 5.0f;

	float Lifespan = 5.0f;
	FTimerHandle LifespanTimer;
	bool Active;
	void Deactivate();
public:	
	// Sets default values for this actor's properties
	AMonsterActor();

	virtual void SetLifeSpan(float InLifespan) override;
	void SetActive(bool InActive);
	bool IsActive();
	//// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
