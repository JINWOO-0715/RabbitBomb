// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"
#include "MainPawn.h"

ARealGameModeBase::ARealGameModeBase()
{

	DefaultPawnClass = AMainPawn::StaticClass();
}