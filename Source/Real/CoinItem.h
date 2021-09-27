// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "CoinItem.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API ACoinItem : public AItemActor
{
	GENERATED_BODY()
	
	public:
	ACoinItem();
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
