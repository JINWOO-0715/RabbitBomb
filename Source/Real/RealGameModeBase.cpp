// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"
#include "RabbitBombGameInstance.h"
#include "PlayerSaveGame.h"
#include "Particles/ParticleSystemComponent.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


ARealGameModeBase::ARealGameModeBase()
{
	//DefaultPawnClass = AMainPawn::StaticClass();
	

	ObjectPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("MonsterPoller"));
	
	StageManageComponent = CreateDefaultSubobject<UStageManageComponent>(TEXT("StageComponent"));

	
	static ConstructorHelpers::FClassFinder<UScoreWidget> ScoreAsset(TEXT("/Game/BP/ScoreWidget"));
	ScoreWidgetClass = ScoreAsset.Class;

	
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


void ARealGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//
// void ARealGameModeBase::ReturnToTitle()
// {
// 	UGameplayStatics::OpenLevel(this, FName("TitleLevel"), true);
// }


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
			//UE_LOG(LogTemp, Warning, TEXT("SaveName : %s"), *LoadGameInstance->SaveName.ToString());
			//UE_LOG(LogTemp, Warning, TEXT("SaveFloat : %f"), LoadGameInstance->BulletPower);

			// 인스턴스에도 레벨에 넘겨주기 위해 저장.
			GameInstanceRef->PlayerPowerLevel =LoadGameInstance->BulletPowerlevel;
			GameInstanceRef->PlayerFireRateLevel = LoadGameInstance->FireRatelevel;
			GameInstanceRef->PlayerHPLevel =LoadGameInstance->MaxHPlevel;
			GameInstanceRef->PlayerSpeedLevel=LoadGameInstance->MoveSpeedlevel;
			GameInstanceRef->PlayerHasCoin = LoadGameInstance->PlayerCoin;
			GameInstanceRef->isStroySaw = LoadGameInstance->PlayerStorySaw; 
			//SetStage(LoadGameInstance->PlayerStage);
			//NowStage = LoadGameInstance->PlayerStage;
			
			
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


//
// void ARealGameModeBase::CheckStage()
// {
// 	// 플레이어안의 몬스터 정보 처리해준다.
// 	 
// 	// 다죽었으면
// 	if (NowMosterCount.eBossMonster < 1 && NowMosterCount.eCommomMonster < 1 && NowMosterCount.eTowerMonster < 1)
// 	{
// 		
// 		// 웨이브를 늘려야하면 늘리고
// 		if(NowWave < GetGoalWave())
// 		{
// 			NowWave++;
// 			NowMosterCount = GoalGameStage->MonsterWave[NowWave];
// 			WorldMonsterManger->ResetCount();
// 			// 리셋해서 다시 스폰하슈
// 			AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
// 			player->PlayerScoreWidget->SetRemainMonsterText(NowMosterCount.eBossMonster+NowMosterCount.eCommomMonster+NowMosterCount.eTowerMonster);
// 			auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
// 			player->PlayerScoreWidget->SetNowWaveText(NowWave,GameInstanceRef->GoalWave);
// 		}
// 		else
// 		{
// 			//스테이지 클리어 메시지를 띄운다
// 			UGameplayStatics::PlaySound2D(this,GameClearSound );
// 			AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
// 			player->PlayerScoreWidget->ShowStageClearBox(true);
// 			
// 			GetWorld()->GetTimerManager().SetTimer(ReturnToTitleTimerHandle, this, &ARealGameModeBase::ReturnToTitle,4);
// 					
// 		
// 		}
//
// 		
// 	}
// }
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

	
	// 레벨에따라 설정
	
	 if (GetWorld()->GetName() == FString("MainLevel"))
	 {
	 	
	 	ObjectPooler->Spawn();
	 	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	 	StageManageComponent->StageStart(GameInstanceRef->NowStage);
	 	PlayerScoreWidget = Cast<UScoreWidget>(CreateWidget(GetWorld(), ScoreWidgetClass));
	 	if(PlayerScoreWidget!=nullptr)
	 	{
	 		PlayerScoreWidget->AddToViewport();
	 		PlayerScoreWidget->SetRemainMonsterText(StageManageComponent->GetRemainMonster());
	 		PlayerScoreWidget->SetNowWaveText(1,StageManageComponent->GoalWave);
	 	}
	
	 }
}


// FMonsterRow* ARealGameModeBase::GetMonsterRowData(int rowN)
// {
// 	FMonsterRow* const MonsterRowData = MonsterData->FindRow<FMonsterRow>(
// 		FName(*(FString::FormatAsNumber(rowN))), FString(""));
// 	
// 	return  MonsterRowData;
// }
//
// FMonsterRow* ARealGameModeBase::GetMonsterRowData(FName mSkillName)
// {
// 	FMonsterRow* const MonsterRowData = MonsterData->FindRow<FMonsterRow>(
// 		mSkillName, FString(""));
//
// 	return MonsterRowData;
// }
//
//


// FGameStateRow* ARealGameModeBase::GetGameStateRowData(int rowN=1)
// {
// 	
// 	FGameStateRow* const GameStateRowData = GameStageData->FindRow<FGameStateRow>(
// 		FName(*(FString::FormatAsNumber(rowN))), FString(""));
//
// 	return GameStateRowData;
// }
// FPlayerSkillRow* ARealGameModeBase::GetPlayerSkillRowDataToNum(int rowN)
// {
// 	FPlayerSkillRow* const PlayerKillRowData = PlayerSkillData->FindRow<FPlayerSkillRow>(
// 		FName(*(FString::FormatAsNumber(rowN))), FString(""));
//
// 	return PlayerKillRowData;
// }
//
// FPlayerSkillRow* ARealGameModeBase::GetPlayerSkillRowDataToNum(FName mSkillName)
// {
// 	FPlayerSkillRow* const PlayerKillRowData = PlayerSkillData->FindRow<FPlayerSkillRow>(
// 		mSkillName, FString(""));
//
// 	return PlayerKillRowData;
// }


