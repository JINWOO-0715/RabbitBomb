// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterDataTable.h"
#include "MonsterActor.generated.h"

UCLASS()
class REAL_API AMonsterActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MonseterMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MonsterHP = 50.f;

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// A스타가 될 상.
	UFUNCTION()
	void MoveToTarget();

	// float LifeSpan = 5.0f;

	//5초동안 살아남기
	float Lifespan = 5.0f;

	// 공속
	float FireRate = 1.0f;
	
	// 총알 속도
	float BulletSpeed = 500.0f;
	
	
	
	// 타이머 핸들 이름
	FTimerHandle LifespanTimer;
	FTimerHandle AttackTimer;
	
//	FTimerHandle MovespanTimer;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	float BulletLifeSpan = 5.0f;

	bool Active;
	bool bCanFire;
	void Deactivate();
	
public:	
	// Sets default values for this actor's properties
	AMonsterActor();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed =100.0f;
	
	//UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	//float MovetoTagetUpdateDuration =0.1f;
	
	virtual void SetLifeSpan(float InLifespan) override;
	void SetActive(bool InActive);
	void ShotTimerExpired();
	void FireShot();
	void InitMonster(int dataRowN);
	
	bool IsActive();
	//// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	//
	// 총알 파워
	float BulletPower = 10.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
