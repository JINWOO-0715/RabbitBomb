// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"

#include "RabbitBombGameInstance.h"
#include "MonsterManager.h"
#include "TowerMonsterActor.h"


#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

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
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("/Game/Particle/P_Impact_Shield_Ice.P_Impact_Shield_Ice"));
	HitedParticle = Particle.Object;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle2(TEXT("/Game/Particle/P_YoYo_Blast_Axe_00.P_YoYo_Blast_Axe_00"));
	DeadParticle = Particle2.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle3(TEXT("/Game/Particle/P_TraceMagic_AreaIce_02.P_TraceMagic_AreaIce_02"));
	DeadParticle2 = Particle3.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> ClickSoundAsset(TEXT("/Game/Sound/ClickSound.ClickSound"));
	ClickSound = ClickSoundAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> UpSoundAsset(TEXT("/Game/Sound/UpStat.UpStat"));
	StatUpSound = UpSoundAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> DeadSoundAsset(TEXT("/Game/Sound/2.2"));
	MonsterDeadSound = DeadSoundAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> DeadSoundAsset2(TEXT("/Game/Sound/POP.POP"));
	MonsterHitSound = DeadSoundAsset2.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> LoseSoundAsset(TEXT("/Game/Sound/endgame.endgame"));
	LoseSound = LoseSoundAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> LoseSoundAsset2(TEXT("/Game/Sound/hited.hited"));
	LoseSound2 = LoseSoundAsset2.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> DeadSoundAsset3(TEXT("/Game/Sound/GameClear.GameClear"));
	GameClearSound = DeadSoundAsset3.Object;
}

void ARealGameModeBase::SetMonsterManager(AMonsterManager* mMonsterManager)
{
	WorldMonsterManger = mMonsterManager;
}


void ARealGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetWorld()->GetRealTimeSeconds();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(GetWorld()->GetRealTimeSeconds()));
}

void ARealGameModeBase::ReturnToTitle()
{
	UGameplayStatics::OpenLevel(this, FName("TitleLevel"), true);
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
		
		auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		
		AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
		SaveGameInstance->PlayerCoin = GameInstanceRef->PlayerHasCoin;
		SaveGameInstance->MaxHPlevel = GameInstanceRef->PlayerHPLevel;
		SaveGameInstance->FireRatelevel = GameInstanceRef->PlayerFireRateLevel;
		SaveGameInstance->MoveSpeedlevel = GameInstanceRef->PlayerSpeedLevel;
		SaveGameInstance->BulletPowerlevel =GameInstanceRef->PlayerPowerLevel;
		SaveGameInstance->PlayerStorySaw = GameInstanceRef->isStroySaw;
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
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	
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

			// 인스턴스에도 레벨에 넘겨주기 위해 저장.
			GameInstanceRef->PlayerPowerLevel =LoadGameInstance->BulletPowerlevel;
			GameInstanceRef->PlayerFireRateLevel = LoadGameInstance->FireRatelevel;
			GameInstanceRef->PlayerHPLevel =LoadGameInstance->MaxHPlevel;
			GameInstanceRef->PlayerSpeedLevel=LoadGameInstance->MoveSpeedlevel;
			GameInstanceRef->PlayerHasCoin = LoadGameInstance->PlayerCoin;
			GameInstanceRef->isStroySaw = LoadGameInstance->PlayerStorySaw; 
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


int ARealGameModeBase::GetGoalWave()
{
	return GoalGameStage->MonsterWave.Num();
}

void ARealGameModeBase::SetNowStage(int mStage)
{
	NowStage=mStage;
}

void ARealGameModeBase::DecreaseCommomMonsterCount()
{
	NowMosterCount.eCommomMonster--;
	
	CheckStage();
}	
void ARealGameModeBase::DecreaseTowerMonsterCount()
{
	NowMosterCount.eTowerMonster--;
	
	CheckStage();
}

void ARealGameModeBase::DecreaseBossMonsterCount()
{
	NowMosterCount.eBossMonster--;
	
	CheckStage();
}

int ARealGameModeBase::GetGoalCommonMonsterCount()
{
	return GoalGameStage->MonsterWave[NowWave].eCommomMonster; 
}

int ARealGameModeBase::GetGoalTowerMonsterCount()
{
	return GoalGameStage->MonsterWave[NowWave].eTowerMonster; 
}

int ARealGameModeBase::GetGoalBossMonsterCount()
{
	return GoalGameStage->MonsterWave[NowWave].eBossMonster; 
}

void ARealGameModeBase::CheckStage()
{
	// 플레이어안의 몬스터 정보 처리해준다.
	 
	// 다죽었으면
	if (NowMosterCount.eBossMonster < 1 && NowMosterCount.eCommomMonster < 1 && NowMosterCount.eTowerMonster < 1)
	{
		
		// 웨이브를 늘려야하면 늘리고
		if(NowWave < GetGoalWave())
		{
			NowWave++;
			NowMosterCount = GoalGameStage->MonsterWave[NowWave];
			WorldMonsterManger->ResetCount();
			// 리셋해서 다시 스폰하슈
			AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			player->PlayerScoreWidget->SetRemainMonsterText(NowMosterCount.eBossMonster+NowMosterCount.eCommomMonster+NowMosterCount.eTowerMonster);
			auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			player->PlayerScoreWidget->SetNowWaveText(NowWave,GameInstanceRef->GoalWave);
		}
		else
		{
			//스테이지 클리어 메시지를 띄운다
			UGameplayStatics::PlaySound2D(this,GameClearSound );
			AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			player->PlayerScoreWidget->ShowStageClearBox(true);
			
			GetWorld()->GetTimerManager().SetTimer(ReturnToTitleTimerHandle, this, &ARealGameModeBase::ReturnToTitle,4);
					
		
		}

		
	}
}
void ARealGameModeBase::BeginPlay()
{
	
	UPlayerSaveGame* LoadGameInstance = Cast<UPlayerSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));

	if (LoadGameInstance)
		Load();

	if(GetWorld()->GetName() == FString("StoryLevel"))
	{
		auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if(GameInstanceRef->isStroySaw)
		{
			UGameplayStatics::OpenLevel(this, FName("TitleLevel"), true);
		}
		GameInstanceRef->isStroySaw = true;
		Save();
	}
	if (GetWorld()->GetName() == FString("MainLevel"))
	{
		//StartTime = 0.0f;
		// 총알 스폰
		
		auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		BulletPooler->Spawn();
		MonsterPooler->Spawn();
		ItemPooler->Spawn();
		PlayerSkillChooseWidget = Cast<UChooseSkillWidget>(CreateWidget(GetWorld(), PlayerSkillChooseClass));
		//FGameStateRow* GameStage = GetGameStateRowData(NowStage);

		AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		
		
		
		// 목표 스테이지 설정
		SetNowStage(GameInstanceRef->NowStage);
		GoalGameStage = GetGameStateRowData(NowStage);
		NowWave =1;
		NowMosterCount.eCommomMonster = GoalGameStage->MonsterWave[NowWave].eCommomMonster;
		NowMosterCount.eTowerMonster = GoalGameStage->MonsterWave[NowWave].eTowerMonster;
		NowMosterCount.eBossMonster = GoalGameStage->MonsterWave[NowWave].eBossMonster;
		// 몬스터 수 UI의 몬스터 수 설정
		
		int MonsterNum = NowMosterCount.eCommomMonster+NowMosterCount.eTowerMonster+NowMosterCount.eBossMonster;
		GameInstanceRef->MonsterCount= MonsterNum;
		// 
		GameInstanceRef->GoalWave = GoalGameStage->MonsterWave.Num();
		GameInstanceRef->NowWave =1; 
		
		// 스테이지의 1wave부터 시작
		UWorld* const World = GetWorld();
		player->SetScoreText();
		Save();
		
		// World->GetTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn,
		//                                   MonsterSpawnCoolTime);
	}
}
FMonsterRow* ARealGameModeBase::GetMonsterRowData(int rowN)
{
	FMonsterRow* const MonsterRowData = MonsterData->FindRow<FMonsterRow>(
		FName(*(FString::FormatAsNumber(rowN))), FString(""));
	
	return  MonsterRowData;
}

FMonsterRow* ARealGameModeBase::GetMonsterRowData(FName mSkillName)
{
	FMonsterRow* const MonsterRowData = MonsterData->FindRow<FMonsterRow>(
		mSkillName, FString(""));

	return MonsterRowData;
}

FGameStateRow* ARealGameModeBase::GetGameStateRowData(int rowN=1)
{
	FGameStateRow* const GameStateRowData = GameStageData->FindRow<FGameStateRow>(
		FName(*(FString::FormatAsNumber(rowN))), FString(""));

	return GameStateRowData;
}
FPlayerSkillRow* ARealGameModeBase::GetPlayerSkillRowDataToNum(int rowN)
{
	FPlayerSkillRow* const PlayerKillRowData = PlayerSkillData->FindRow<FPlayerSkillRow>(
		FName(*(FString::FormatAsNumber(rowN))), FString(""));

	return PlayerKillRowData;
}

FPlayerSkillRow* ARealGameModeBase::GetPlayerSkillRowDataToNum(FName mSkillName)
{
	FPlayerSkillRow* const PlayerKillRowData = PlayerSkillData->FindRow<FPlayerSkillRow>(
		mSkillName, FString(""));

	return PlayerKillRowData;
}


