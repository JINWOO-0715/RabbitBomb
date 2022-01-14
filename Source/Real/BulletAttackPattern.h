// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletAttackPattern.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UBulletAttackPattern : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletAttackPattern();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// hasactor -> fireshot

	UFUNCTION(BlueprintCallable)
	void TargetShot(const AActor* Target,  const float BulletSpeed);

	UFUNCTION(BlueprintCallable)
	void CirCleShot( const float BulletSpeed);
	
	UFUNCTION(BlueprintCallable)
	void StarShot();
	
	UFUNCTION(BlueprintCallable)	
	void CircularsectorShot();
		
	UFUNCTION(BlueprintCallable)
	void OneStraightShot(const FVector ForwardVector);

	UFUNCTION(BlueprintCallable)
	void ThreeStraightShot(const FVector ForwardVector);

	UFUNCTION(BlueprintCallable)
	void FiveStraightShot(const FVector ForwardVector);

	UFUNCTION(BlueprintCallable)
	void SevenStraightShot(const FVector ForwardVector);


	
	UFUNCTION(BlueprintCallable)
	void FireStraightRandom();
	
	//실시간으로 
	//FireShot  => 근거리 
	//CircleShot =>  원거리 

	

		
};
