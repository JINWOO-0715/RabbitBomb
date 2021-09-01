// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IceSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UIceSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIceSkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
	FName SkillName;

	UPROPERTY(BlueprintReadWrite)
	AActor* OwnerActor;
	
	UPROPERTY(BlueprintReadWrite)
	bool bCanFire =false;
	
	UPROPERTY(BlueprintReadWrite)
	float SkillCoolTime;
	void IceCircleAttack();
	void ShotTimerExpired();
	FTimerHandle TimerHandle_ShotTimerExpired;

};

