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
	// ÃÑ¾Ë ½ºÆù
	BulletPooler->Spawn();

	//À§Á¬ »ý¼º
	PlayerRightWidget = Cast<URightWidget>(CreateWidget(GetWorld(),PlayerRightWidgetClass));
	if(PlayerRightWidgetClass !=nullptr)
	{
		if(PlayerRightWidget)
		{
			PlayerRightWidget->AddToViewport();
	 		//PlayerRightWidget->SetPlayer();
			UE_LOG(LogTemp,Warning,TEXT("sucess wiget"));
		}
		// PlayerRightWidget->Player=this;
		// PlayerRightWidget->AddToViewport();
		
	}
	
}

