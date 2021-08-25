// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "NavigationSystem.h"

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
	// �Ѿ� ����
	BulletPooler->Spawn();
	MonsterPooler->Spawn();


	//���� ����
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

	UWorld* const World = GetWorld();
	World->GetTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, MonsterSpawnCoolTime);
	
}

void ARealGameModeBase:: MonsterSpawn()
{
	UWorld* const World = GetWorld();
	
	AMonsterActor* Monster = MonsterPooler->GetPooledMonster();
		
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
		GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
		return;
	}
	// ������ġ�� �����ϰ�
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	auto result = FMath::VRand();
	// �� 800~1500������ �����ϰ�.
	result *= FMath::RandRange(800,1500);
	result *= FVector(1.f,1.f,0.f);
	result+=player->GetActorLocation();
	Monster->SetActorLocation(result);
	
	// ���� ��ȣ�� ������ �ʱ�ȭ�Ѵ�
	Monster->InitMonster(MonsterNum);

	// �����Ѵ�
	Monster->SetActive(true);

	GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, MonsterSpawnCoolTime);
	UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));

}