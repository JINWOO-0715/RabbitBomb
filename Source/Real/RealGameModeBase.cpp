// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "MainPawn.h"

ARealGameModeBase::ARealGameModeBase()
{
	DefaultPawnClass = AMainPawn::StaticClass();

	BulletPooler = CreateDefaultSubobject<UBulletPoolComopnent>(TEXT("BulletPoller"));

	//BulletPooler->SetupAttachment(RootComponent);
	MonsterPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("MonsterPoller"));

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/BP/MonsterDT"));
	if (DataTable.Succeeded())
	{
		LevelUpDataTable = DataTable.Object;
	}
}

FMonsterRow* ARealGameModeBase::GetMonsterRowData(int rowN)
{
	FMonsterRow* MonsterRowData = LevelUpDataTable->FindRow<FMonsterRow>(
FName(*(FString::FormatAsNumber(rowN))), FString(""));
	if(MonsterRowData)
	{
		UE_LOG(LogTemp, Warning, TEXT("sucess Init"));
	}
	

	return MonsterRowData;
}


void ARealGameModeBase::BeginPlay()
{
	// ÃÑ¾Ë ½ºÆù
	BulletPooler->Spawn();
	MonsterPooler->Spawn();


	//À§Á¬ »ý¼º
	PlayerRightWidget = Cast<URightWidget>(CreateWidget(GetWorld(), PlayerRightWidgetClass));
	if (PlayerRightWidgetClass != nullptr)
	{
		if (PlayerRightWidget)
		{
			PlayerRightWidget->AddToViewport();
			//PlayerRightWidget->SetPlayer();
			UE_LOG(LogTemp, Warning, TEXT("sucess wiget"));
		}
		// PlayerRightWidget->Player=this;
		// PlayerRightWidget->AddToViewport();
	}
}

