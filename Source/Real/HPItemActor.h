// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "HPItemActor.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API AHPItemActor : public AItemActor
{
	GENERATED_BODY()

	public:
	AHPItemActor();

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

};
