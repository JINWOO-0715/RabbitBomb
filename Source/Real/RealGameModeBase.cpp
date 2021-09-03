// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "ChooseSkillWidget.h" 
#include "ItemActor.h"


ARealGameModeBase::ARealGameModeBase()
{
	//DefaultPawnClass = AMainPawn::StaticClass();

	BulletPooler = CreateDefaultSubobject<UBulletPoolComopnent>(TEXT("BulletPoller"));
	
	MonsterPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("MonsterPoller"));

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterDataAsset(TEXT("/Game/BP/MonsterDT"));
	if (MonsterDataAsset.Succeeded())
	{
		MonsterData = MonsterDataAsset.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerSkillDataAsset(TEXT("/Game/BP/PlayerSkillDT"));
	if (PlayerSkillDataAsset.Succeeded())
	{
		PlayerSkillData = PlayerSkillDataAsset.Object;
	}
}


void ARealGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetWorld()->GetRealTimeSeconds();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(GetWorld()->GetRealTimeSeconds()));
	
}

FMonsterRow* ARealGameModeBase::GetMonsterRowData(int rowN)
{
	FMonsterRow* MonsterRowData = MonsterData->FindRow<FMonsterRow>(
			FName(*(FString::FormatAsNumber(rowN))), FString(""));

	return MonsterRowData;
}

FMonsterRow* ARealGameModeBase::GetMonsterRowData(FName mSkillName)
{
	FMonsterRow* MonsterRowData = MonsterData->FindRow<FMonsterRow>(
		mSkillName, FString(""));

	return MonsterRowData;
}

FPlayerSkillRow* ARealGameModeBase::GetPlayerSkillRowDataToNum(int rowN)
{
	FPlayerSkillRow* PlayerKillRowData = PlayerSkillData->FindRow<FPlayerSkillRow>(
			FName(*(FString::FormatAsNumber(rowN))), FString(""));
	
	 return PlayerKillRowData;
}

FPlayerSkillRow* ARealGameModeBase::GetPlayerSkillRowDataToNum(FName mSkillName)
{
	FPlayerSkillRow* PlayerKillRowData = PlayerSkillData->FindRow<FPlayerSkillRow>(
		mSkillName, FString(""));
	
	return PlayerKillRowData;
}


void ARealGameModeBase::BeginPlay()
{
	StartTime=0.0f;
	// 총알 스폰
	BulletPooler->Spawn();
	MonsterPooler->Spawn();
	
	


	// //위젯 생성
	// PlayerRightWidget = Cast<URightWidget>(CreateWidget(GetWorld(), PlayerRightWidgetClass));
	// if (PlayerRightWidgetClass != nullptr)
	// {
	// 	if (PlayerRightWidget)
	// 	{
	// 		PlayerRightWidget->AddToViewport();
	// 		//PlayerRightWidget->SetPlayer();
	// 		UE_LOG(LogTemp, Warning, TEXT("sucess wiget"));
	// 	}
	// 	// PlayerRightWidget->Player=this;
	// 	// PlayerRightWidget->AddToViewport();
	// }
	
	PlayerSkillChooseWidget = Cast<UChooseSkillWidget>(CreateWidget(GetWorld(), PlayerSkillChooseClass));
	if (PlayerSkillChooseClass != nullptr)
	{
		
		// PlayerSkillChooseWidget->Player=this;
		// PlayerRightWidget->AddToViewport();
	}

	UWorld* const World = GetWorld();
	World->GetTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, MonsterSpawnCoolTime);
	
}

void ARealGameModeBase:: MonsterSpawn()
{
	UWorld* const World = GetWorld();
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	auto result = FMath::VRand();

	
	// 몬스터 몇마리 도 랜덤하게 (최소 1마리 ~최대 몇마리)
	int const randMonsterMun = FMath::RandRange(SpawnMonsterRandomNumMin,SpawnMonsterRandomNumMax);
	MonsterSpawnNum+=randMonsterMun;
	// 몬스터 생성
	for(int i =0 ; i<MonsterSpawnNum;i++)
	{
		AMonsterActor* Monster = MonsterPooler->GetPooledMonster();
		// 몬스터 범위  (SpawnRangeMin,SpawnRangeMax) 랜덤하게
		result *= FMath::RandRange(SpawnRangeMin,SpawnRangeMax);
		if (Monster == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
			GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
			return;
		}
	
		result *= FVector(1.f,1.f,0.f);
		result+=player->GetActorLocation();
		Monster->SetActorLocation(result);

		
		// 몬스터 번호를 가져와 초기화한다
		Monster->InitMonster(MonsterType);

		// 실행한다
		Monster->SetActive(true);
	}


	//쿨타임 랜덤하게 조절
	float const RandCoolTime = FMath::RandRange(SpawnCoolTimeRandomMin,SpawnCoolTimeRandomMax);
	MonsterSpawnCoolTime+=RandCoolTime;
	GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, MonsterSpawnCoolTime);
	UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));

}