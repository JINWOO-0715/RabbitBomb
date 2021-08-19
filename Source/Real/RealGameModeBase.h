// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RealGameModeBase.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ARealGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Spawner")
	UBulletPoolComopnent* BulletPooler;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	bool trigger;
	


protected:
	virtual void BeginPlay() override;
public:
	ARealGameModeBase();
	
};
