// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"

#include "TowerMonsterActor.h"


ARealGameModeBase::ARealGameModeBase()
{
	//DefaultPawnClass = AMainPawn::StaticClass();

	BulletPooler = CreateDefaultSubobject<UBulletPoolComopnent>(TEXT("BulletPoller"));

	MonsterPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("MonsterPoller"));

	ItemPooler = CreateDefaultSubobject<UItemPoolComponent>(TEXT("ItemPoller"));

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
	
	static ConstructorHelpers::FObjectFinder<UDataTable> GameDataAsset(TEXT("/Game/BP/GameStateDT"));
	if (GameDataAsset.Succeeded())
	{
		GameStageData = GameDataAsset.Object;
	}
}


void ARealGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetWorld()->GetRealTimeSeconds();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(GetWorld()->GetRealTimeSeconds()));
}


void ARealGameModeBase::Save()
{
	UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		/** Save file data **/
		SaveGameInstance->SaveSlotName = "MySaveGame";
		SaveGameInstance->SaveIndex = 0;
		/** Save data **/
		SaveGameInstance->SaveName = "Player0";


		AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
		SaveGameInstance->PlayerCoin = player->GetCoin();
		SaveGameInstance->MaxHPlevel = player->GetMaxHPlevel();
		SaveGameInstance->FireRatelevel = player->GetFireRatelevel();
		SaveGameInstance->MoveSpeedlevel = player->GetMoveSpeedlevel();
		SaveGameInstance->BulletPowerlevel = player->GetBulletPowerlevel();
		//SaveGameInstance->PlayerStage =  GetStage();
		
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGameInstance is nullptr"));
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->SaveIndex);
}

void ARealGameModeBase::Load()
{
	UPlayerSaveGame* LoadGameInstance = Cast<UPlayerSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	if (LoadGameInstance)
	{
		LoadGameInstance->SaveSlotName = "MySaveGame";
		LoadGameInstance->SaveIndex = 0;

		LoadGameInstance = Cast<UPlayerSaveGame>(
			UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->SaveIndex));


		AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (LoadGameInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("SaveName : %s"), *LoadGameInstance->SaveName.ToString());
			UE_LOG(LogTemp, Warning, TEXT("SaveFloat : %f"), LoadGameInstance->BulletPower);
			
			player->SetPlayerCoin(LoadGameInstance->PlayerCoin);
			player->SetBulletPowerLevel(LoadGameInstance->BulletPowerlevel);
			player->SetFireRateLevel(LoadGameInstance->FireRatelevel);
			player->SetMaxHpLevel(LoadGameInstance->MaxHPlevel);
			player->SetMoveSpeedLevel(LoadGameInstance->BulletPowerlevel);
			//SetStage(LoadGameInstance->PlayerStage);
			NowStage = LoadGameInstance->PlayerStage;
		
			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SaveGameInstance is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGameInstance is nullptr"));
	}
}

int ARealGameModeBase::GetGoalCommonMonsterCount()
{
	
	return GoalGameStage->MonsterWave[NowWave].eCommomMonster; 
}

int ARealGameModeBase::GetGoalWave()
{
	return GoalGameStage->MonsterWave.Num();
}

void ARealGameModeBase::ChangeStage()
{
	NowStage++;
	GoalGameStage = GetGameStateRowData(NowStage);

}

// void ARealGameModeBase::UpCommomMonsterCount()
// {
// 	WaveMonsterCount.eCommomMonster ++;
// }
//
//
// void ARealGameModeBase::UpTowerMonsterCount()
// {
// 	WaveMonsterCount.eTowerMonster++;
// }
//
// void ARealGameModeBase::UpBossMonsterCount()
// {
// 	WaveMonsterCount.eBossMonster++;
// }
//
// void ARealGameModeBase::SetStage(int mStage)
// {
// 	NowStage = mStage;
// 	WaveMonsterCount.eBossMonster =0;
// 	WaveMonsterCount.eCommomMonster =0;
// 	WaveMonsterCount.eTowerMonster =0;
// 	
// }
//
// bool ARealGameModeBase::isSpawnAble()
// {
// 	if(GoalGameStage->MonsterWave[NowStage].eCommomMonster > WaveMonsterCount.eCommomMonster)
// 	{
// 		return true;
// 	}
// 	if(GoalGameStage->MonsterWave[NowStage].eTowerMonster > WaveMonsterCount.eTowerMonster)
// 	{
// 		return true;
// 	}
// 	if(GoalGameStage->MonsterWave[NowStage].eBossMonster > WaveMonsterCount.eBossMonster)
// 	{
// 		return true;
// 	}
//
// 	return false;
// }


void ARealGameModeBase::BeginPlay()
{
	
	UPlayerSaveGame* LoadGameInstance = Cast<UPlayerSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	if (LoadGameInstance)
		Load();

	if (GetWorld()->GetName() == FString("MainLevel"))
	{
		//StartTime = 0.0f;
		// 총알 스폰
		BulletPooler->Spawn();
		MonsterPooler->Spawn();
		ItemPooler->Spawn();
		PlayerSkillChooseWidget = Cast<UChooseSkillWidget>(CreateWidget(GetWorld(), PlayerSkillChooseClass));
		//FGameStateRow* GameStage = GetGameStateRowData(NowStage);
		// 목표 스테이지 설정
		GoalGameStage = GetGameStateRowData(NowStage);
		
		NowWave =1;
		// 스테이지의 1wave부터 시작
		
		UWorld* const World = GetWorld();
	
		
		// World->GetTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn,
		//                                   MonsterSpawnCoolTime);
	}
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

FGameStateRow* ARealGameModeBase::GetGameStateRowData(int rowN=1)
{
	FGameStateRow* GameStateRowData = GameStageData->FindRow<FGameStateRow>(
		FName(*(FString::FormatAsNumber(rowN))), FString(""));

	return GameStateRowData;
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


void ARealGameModeBase::MonsterSpawn()
{
	UWorld* const World = GetWorld();
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// 
	FVector result = FMath::VRand();

	AMonsterActor* Monster = MonsterPooler->GetPooledMonster();
	ATowerMonsterActor* TowerMonster = MonsterPooler->GetPooledTowerMonster();
	ABossMonsterActor* BossMonster = MonsterPooler->GetPooledBossMonster();
	float const time = GetWorld()->GetAudioTimeSeconds();

	if(time <=60.f)
	{
		SpawnMonsterRandomNumMin =1;
		SpawnMonsterRandomNumMax =2;
		SpawnCoolTimeRandomMin = 3.f;
		SpawnCoolTimeRandomMax = 4.f;
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("stage1"));
	}

	// 몬스터 몇마리 랜덤하게 (최소  ~최대 )
	int const randMonsterMun = FMath::RandRange(SpawnMonsterRandomNumMin, SpawnMonsterRandomNumMax);

	// // 몬스터 생성
	// for (int i = 0; i < (MonsterSpawnNum + randMonsterMun); i++)
	// {
	//
	// 	result = FMath::VRand();
	// 	int32 RandomRange =FMath::RandRange(SpawnRangeMin, SpawnRangeMax);
	// 	result *= FMath::RandRange(SpawnRangeMin, SpawnRangeMax);
	// 	// 단계 조절
	// 	result *= FVector(1.f, 1.f, 0.f);
	// 	result += player->GetActorLocation();
	// 	
	// 	if((result.X>3000) || (result.X<-3000) || (result.Y>3000)||  (result.Y<-3000))
	// 	{
	// 		result.X = FMath::RandRange(-2500, 2500);
	// 		result.Y = FMath::RandRange(-2500, 2500);
	// 	}
	// 	//MonsterType = FMath::RandRange(1, 3);
	// 	if(time <60.f)
	// 	{ 
	// 		MonsterType =1;
	// 	}
	// 	else 
	// 	{
	// 		MonsterType =1;
	// 		
	// 		if(i<3)
	// 		{
	// 			MonsterType =2;
	// 			
	// 		}
	// 		if(!isBossSpawn)
	// 		{
	// 			isBossSpawn=true;
	// 			MonsterType=4;
	//
	// 		}
	// 	}
	//
	// 	
	// 	
	// 	switch (MonsterType)
	// 	{
	// 	case 1:
	// 		Monster = MonsterPooler->GetPooledMonster();
	// 		Monster->SetActorLocation(result);
	// 		// 몬스터 번호를 가져와 초기화한다 
	// 		Monster->InitMonster(MonsterType);
	// 		Monster->SetActive(true);
	// 		if (Monster == nullptr)
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
	// 			GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
	// 			return;
	// 		}
	// 		break;
	// 	case 2:
	// 	case 3:
	// 		TowerMonster = MonsterPooler->GetPooledTowerMonster();
	// 		TowerMonster->SetActorLocation(result);
	// 		// 몬스터 번호를 가져와 초기화한다 
	// 		TowerMonster->InitMonster(MonsterType);
	// 		TowerMonster->SetActive(true);
	// 		if (TowerMonster == nullptr)
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
	// 			GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
	// 			return;
	// 		}
	// 		break;
	// 	case 4:
	// 		BossMonster = MonsterPooler->GetPooledBossMonster();
	// 		BossMonster->SetActorLocation(result);
	// 		// 몬스터 번호를 가져와 초기화한다 
	// 		BossMonster->InitMonster(MonsterType);
	// 		BossMonster->SetActive(true);
	// 		if (BossMonster == nullptr)
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
	// 			GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
	// 			return;
	// 		}
	// 		break;
	// 	default:
	// 		Monster = MonsterPooler->GetPooledMonster();
	// 		Monster->SetActorLocation(result);
	// 		// 몬스터 번호를 가져와 초기화한다 
	// 		Monster->InitMonster(MonsterType);
	// 		Monster->SetActive(true);
	// 		if (Monster == nullptr)
	// 		{
	// 			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
	// 			GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
	// 			return;
	// 		}
	// 		break;
	// 	}
	// }
	// //쿨타임 랜덤하게 조절
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(time));
	// // float const RandCoolTime = FMath::RandRange(SpawnCoolTimeRandomMin, SpawnCoolTimeRandomMax);
	//
	// GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, MonsterSpawnCoolTime + RandCoolTime);
	// UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));
}
