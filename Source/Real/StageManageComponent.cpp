// Fill out your copyright notice in the Description page of Project Settings.


#include "StageManageComponent.h"

#include "BossMonster.h"
#include "RealGameModeBase.h"

// Sets default values for this component's properties
UStageManageComponent::UStageManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent=true;
	// ...

	static ConstructorHelpers::FObjectFinder<UDataTable> StageAsset(TEXT("/Game/BP/GameStageDT"));
	if (StageAsset.Succeeded())
	{
		GameStageData = StageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterDataAsset(TEXT("/Game/BP/CommonMonsterDT.CommonMonsterDT"));
	if (MonsterDataAsset.Succeeded())
	{
		CommonMonsterData = MonsterDataAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> BossMonsterDataAsset(TEXT("/Game/BP/BossMonsterDT.BossMonsterDT"));
	if (BossMonsterDataAsset.Succeeded())
	{
		BossMonsterData = BossMonsterDataAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> TowerMonsterDataAsset(TEXT("/Game/BP/TowerMonsterDT.TowerMonsterDT"));
	if (TowerMonsterDataAsset.Succeeded())
	{
		TowerMonsterData = TowerMonsterDataAsset.Object;
	}
	
	NowWave=1;
	NowStage=1;
	SpawnCoolTime =0.5f;
	NowWaveMonsterCount.CommonMonsterSpawnCount = 0; 
	NowWaveMonsterCount.TowerMonsterSpawnCount = 0;
	NowWaveMonsterCount.BossMonsterSpawnCount =  0;
	
	SpawnPoints.Push(FVector(1400.f,0.f,50.f));
	SpawnPoints.Push(FVector(-1400.f,1400.f,50.f));
	SpawnPoints.Push(FVector(0.f,-1400.f,50.f));
	SpawnPoints.Push(FVector(1400.f,0.f,50.f));
	SpawnPoints.Push(FVector(-1400.f,0.f,50.f));
	SpawnPoints.Push(FVector(0.f,1400.f,50.f));
	SpawnPoints.Push(FVector(1400.f,-1400.f,50.f));
	SpawnPoints.Push(FVector(-1400.f,-1400.f,50.f));

	
}


FGameStageRow* UStageManageComponent::GetGameStateRowData(int rowN) const
{
	if(IsValid(GameStageData))
	{
		FGameStageRow* const GameStageRowData = GameStageData->FindRow<FGameStageRow>(
	FName(*(FString::FormatAsNumber(rowN))), FString(""));

		return GameStageRowData;
	}
	
	UE_LOG(LogTemp, Warning,TEXT("GameStageData is Not Valid"));
	return nullptr;

}

FCommonMonsterData* UStageManageComponent::GetCommonMonsterRowData(int rowN) const
{
	if(IsValid(CommonMonsterData))
	{
	FCommonMonsterData* const MonsterDataRowData = CommonMonsterData->FindRow<FCommonMonsterData>(
		FName(*(FString::FormatAsNumber(rowN))), FString(""));

		return MonsterDataRowData;
	}
	UE_LOG(LogTemp, Warning,TEXT("FCommonMonsterData is Not Valid"));
	return nullptr;
}

FTowerMonsterData* UStageManageComponent::GetTowerMonsterRowData(int rowN) const
{
	if(IsValid(TowerMonsterData))
	{
		FTowerMonsterData* const MonsterDataRowData = TowerMonsterData->FindRow<FTowerMonsterData>(
			FName(*(FString::FormatAsNumber(rowN))), FString(""));

		return MonsterDataRowData;
	}
	UE_LOG(LogTemp, Warning,TEXT("FTowerMonsterData is Not Valid"));
	return nullptr;
}

FBossMonsterData* UStageManageComponent::GetBossMonsterRowData(int rowN) const
{
	if(IsValid(BossMonsterData))
	{
		FBossMonsterData* const MonsterDataRowData = BossMonsterData->FindRow<FBossMonsterData>(
			FName(*(FString::FormatAsNumber(rowN))), FString(""));

		return MonsterDataRowData;
	}
	UE_LOG(LogTemp, Warning,TEXT("FBossMonsterData is Not Valid"));
	return nullptr;
}


void UStageManageComponent::StageStart(int StageNum , int WaveNum)
{
	// 스테이지 정보를 저장
	NowStage = StageNum;
	
	//Wave와 몬스터수 초기화
	NowWave=WaveNum;
	NowWaveMonsterCount.CommonMonsterSpawnCount = 0; 
	NowWaveMonsterCount.TowerMonsterSpawnCount = 0;
	NowWaveMonsterCount.BossMonsterSpawnCount =  0;

	//죽인 몬스터수 초기화
	MonsterDeadCount.CommonMonsterSpawnCount =0;
	MonsterDeadCount.TowerMonsterSpawnCount =0;
	MonsterDeadCount.BossMonsterSpawnCount =0;
	
	// 스테이지 정보(웨이브)를 얻습니다.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	
	//SpawnCoolTime마다 몬스터 소환하기.
	GetWorld()->GetTimerManager().SetTimer(CommonMonsterSpawnTimer, this, &UStageManageComponent::SpawnCommonMonster, 0.5f,true);
	GetWorld()->GetTimerManager().SetTimer(TowerMonsterSpawnTimer, this, &UStageManageComponent::SpawnTowerMonster, SpawnCoolTime,true);
	GetWorld()->GetTimerManager().SetTimer(BossMonsterSpawnTimer, this, &UStageManageComponent::SpawnBossMonster, SpawnCoolTime,true);
}

void UStageManageComponent::SpawnCommonMonster()
{
	// 스테이지 정보(웨이브)를 얻습니다.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	// 몬스터의 타입을 얻습니다.
	const FCommonMonsterData*  StageCommonMonsterData = GetCommonMonsterRowData(NowStageData->CommonMonsterType);
	UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
	
	// CommonMonster가 소환완료되면 타이머를 종료한다.
	if(NowWaveMonsterCount.CommonMonsterSpawnCount == NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(CommonMonsterSpawnTimer);
		UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
		return;
		
	}
	
	// 몬스터를 소환합니다.
	if(NowStageData !=nullptr)
	{
		// CommonMonster소환
		if(NowStageData->MonsterWave.Num()!=0)
		{
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

			//Wave의 몬스터를 적용하기 위해 퓰링된 몬스터를 가져옵니다.
			ACommonMonster* TmpCommonMonster = gm->ObjectPooler->GetPooledCommonMonster();
			if(TmpCommonMonster==nullptr)
			{
				UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
				return;
			}
			// 몬스터 타입으로 초기화해서 활성화해줍니다.
			TmpCommonMonster->InitMonster(StageCommonMonsterData);
			TmpCommonMonster->SetActive(true);
			// 랜덤한 위치에 소환합니다. 
			int RandomPoint = FMath::RandRange(0,SpawnPoints.Num()-1);
			TmpCommonMonster->SetActorLocation(SpawnPoints[RandomPoint]);
			// 현재 소환된 CommonMonster수를 늘립니다. 
			NowWaveMonsterCount.CommonMonsterSpawnCount++;
		
		}
		else
		{
			UE_LOG(LogTemp, Warning,TEXT("NowStage->MonsterWave.Num() is Empty!!!"));
		}
		
	}

}

void UStageManageComponent::SpawnTowerMonster()
{
	// 스테이지 정보(웨이브)를 얻습니다.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	// CommonMonster가 소환완료되면 타이머를 종료한다.
	if(NowWaveMonsterCount.TowerMonsterSpawnCount == NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(TowerMonsterSpawnTimer);
		return;
	}
	

	// 몬스터의 타입을 얻습니다.
	const FTowerMonsterData*  StageTowerMonsterData = GetTowerMonsterRowData(NowStageData->TowerMonsterType);
	
	// 몬스터를 소환합니다.
	if(NowStageData !=nullptr)
	{
		// CommonMonster소환
		if(NowStageData->MonsterWave.Num()!=0)
		{
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

			//Wave의 몬스터를 적용하기 위해 퓰링된 몬스터를 가져옵니다.
			ATowerMonster* TmpTowerMonster = gm->ObjectPooler->GetPooledTowerMonster();
			if(TmpTowerMonster==nullptr)
			{
				UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
				return;
			}
			// 몬스터 타입으로 초기화해서 활성화해줍니다.
			TmpTowerMonster->InitMonster(StageTowerMonsterData);
			TmpTowerMonster->SetActive(true);
			// 랜덤한 위치에 소환합니다. 
			int RandomPoint = FMath::RandRange(0,SpawnPoints.Num()-1);
			TmpTowerMonster->SetActorLocation(SpawnPoints[RandomPoint]);
			// 현재 소환된 CommonMonster수를 늘립니다. 
			NowWaveMonsterCount.TowerMonsterSpawnCount++;
		
		}
		else
		{
			UE_LOG(LogTemp, Warning,TEXT("NowStage->MonsterWave.Num() is Empty!!!"));
		}
		
	}
}

void UStageManageComponent::SpawnBossMonster()
{
	// 스테이지 정보(웨이브)를 얻습니다.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	// CommonMonster가 소환완료되면 타이머를 종료한다.
	if(NowWaveMonsterCount.BossMonsterSpawnCount == NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(BossMonsterSpawnTimer);
		return;
	}
	

	// 몬스터의 타입을 얻습니다.
	const FBossMonsterData*  StageBossMonsterData = GetBossMonsterRowData(NowStageData->BossMonsterType);
	
	// 몬스터를 소환합니다.
	if(NowStageData !=nullptr)
	{
		// CommonMonster소환
		if(NowStageData->MonsterWave.Num()!=0)
		{
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

			//Wave의 몬스터를 적용하기 위해 퓰링된 몬스터를 가져옵니다.
			ABossMonster* TmpCommonMonster = gm->ObjectPooler->GetPooledBossMonster();
			if(TmpCommonMonster==nullptr)
			{
				UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
				return;
			}
			// 몬스터 타입으로 초기화해서 활성화해줍니다.
			TmpCommonMonster->InitMonster(StageBossMonsterData);
			TmpCommonMonster->SetActive(true);
			// 랜덤한 위치에 소환합니다. 
			int RandomPoint = FMath::RandRange(0,SpawnPoints.Num()-1);
			TmpCommonMonster->SetActorLocation(SpawnPoints[RandomPoint]);
			// 현재 소환된 CommonMonster수를 늘립니다. 
			NowWaveMonsterCount.BossMonsterSpawnCount++;
		
		}
		else
		{
			UE_LOG(LogTemp, Warning,TEXT("NowStage->MonsterWave.Num() is Empty!!!"));
		}
		
	}

}

void UStageManageComponent::DecreaseDeadCommonMonster()
{
	MonsterDeadCount.CommonMonsterSpawnCount++;
	IsClearWave();
}

void UStageManageComponent::DecreaseDeadTowerMonster()
{	MonsterDeadCount.TowerMonsterSpawnCount++;
	IsClearWave();
}

void UStageManageComponent::DecreaseDeadBossMonster()
{	MonsterDeadCount.BossMonsterSpawnCount++;
	IsClearWave();
}

void UStageManageComponent::WaveStart()
{

}


void UStageManageComponent::IsClearWave()
{
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	
	// 몬스터를 다 잡았다면
	if(MonsterDeadCount.CommonMonsterSpawnCount == NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount &&
		MonsterDeadCount.TowerMonsterSpawnCount == NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount&&
		MonsterDeadCount.BossMonsterSpawnCount == NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount)
	{
		auto c = NowStageData->MonsterWave.Num();
		UE_LOG(LogTemp, Warning,TEXT("NowWave : %d  & MonsterWave: %d"),NowWave,c);
		// 웨이브가 남았다면 다음웨이브로
		if(NowWave < NowStageData->MonsterWave.Num())
		{
			NowWave+=1;
			NowWaveMonsterCount.CommonMonsterSpawnCount = 0; 
			NowWaveMonsterCount.TowerMonsterSpawnCount = 0;
			NowWaveMonsterCount.BossMonsterSpawnCount = 0;

			MonsterDeadCount.CommonMonsterSpawnCount =0;
			MonsterDeadCount.TowerMonsterSpawnCount =0;
			MonsterDeadCount.BossMonsterSpawnCount =0;
			
			GetWorld()->GetTimerManager().SetTimer(CommonMonsterSpawnTimer, this, &UStageManageComponent::SpawnCommonMonster, SpawnCoolTime,true);
		}
		// 아니라면 스테이지 클리어
		else
		{
			StageClear();
		}
	}
	
	
		
}

void UStageManageComponent::StageClear()
{

	//UGameplayStatics::PlaySound2D(this,GameClearSound );
	AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	player->PlayerScoreWidget->ShowStageClearBox(true);
	GetWorld()->GetTimerManager().SetTimer(ReturnToTile, this, &UStageManageComponent::ReturnToTitle,4);
	
	
}
void UStageManageComponent::ReturnToTitle()
{
	UGameplayStatics::OpenLevel(this, FName("TitleLevel"), true);
}
// Called when the game starts
void UStageManageComponent::BeginPlay()
{
	Super::BeginPlay();
	

	// ...
	
}

void UStageManageComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
}


// Called every frame
void UStageManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

