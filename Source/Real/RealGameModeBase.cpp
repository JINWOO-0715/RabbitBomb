// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MainPawn.h"

ARealGameModeBase::ARealGameModeBase()
{

	DefaultPawnClass = AMainPawn::StaticClass();
	BulletPooler= CreateDefaultSubobject<UBulletPoolComopnent>(TEXT("ObjectPoller"));
	
}
void ARealGameModeBase::BeginPlay()
{
	BulletPooler->Spawn();
	
}

