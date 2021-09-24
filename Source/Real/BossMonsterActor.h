// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterActor.h"
#include "RealGameModeBase.h"
#include "BossMonsterActor.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API ABossMonsterActor : public AMonsterActor
{
	GENERATED_BODY()


	private:
	
	FTimerHandle BossAttackTimer;
	int BossBulletPattern;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	int AttackCount =0;
	public:
	ABossMonsterActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void FireShot() override;

	void FireCircleShot();
	void FireStraight();
	void FireStraightRandom();
	void FireCircularsector();
	void ReverseFireCircularsector();
	void FireShotStar();

	
};
