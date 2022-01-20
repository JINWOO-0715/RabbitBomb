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

int UStageManageComponent::GetRemainMonster()
{
	return RemainMonster;
}


void UStageManageComponent::StageStart(int StageNum , int WaveNum)
{
	// �������� ������ ����
	NowStage = StageNum;

	//Wave�� ���ͼ� �ʱ�ȭ
	NowWave=WaveNum;
	NowWaveMonsterCount.CommonMonsterSpawnCount = 0; 
	NowWaveMonsterCount.TowerMonsterSpawnCount = 0;
	NowWaveMonsterCount.BossMonsterSpawnCount =  0;

	//���� ���ͼ� �ʱ�ȭ
	MonsterDeadCount.CommonMonsterSpawnCount =0;
	MonsterDeadCount.TowerMonsterSpawnCount =0;
	MonsterDeadCount.BossMonsterSpawnCount =0;
	
	// �������� ����(���̺�)�� ����ϴ�.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	
	//SpawnCoolTime���� ���� ��ȯ�ϱ�.
	GetWorld()->GetTimerManager().SetTimer(CommonMonsterSpawnTimer, this, &UStageManageComponent::SpawnCommonMonster, 0.5f,true);
	GetWorld()->GetTimerManager().SetTimer(TowerMonsterSpawnTimer, this, &UStageManageComponent::SpawnTowerMonster, SpawnCoolTime,true);
	GetWorld()->GetTimerManager().SetTimer(BossMonsterSpawnTimer, this, &UStageManageComponent::SpawnBossMonster, SpawnCoolTime,true);

	GoalWave =NowStageData->MonsterWave.Num();
RemainMonster = (NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount - MonsterDeadCount.CommonMonsterSpawnCount) +
	NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount-MonsterDeadCount.TowerMonsterSpawnCount+NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount-
	MonsterDeadCount.BossMonsterSpawnCount;	
	
}

void UStageManageComponent::SpawnCommonMonster()
{
	// �������� ����(���̺�)�� ����ϴ�.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	// ������ Ÿ���� ����ϴ�.
	const FCommonMonsterData*  StageCommonMonsterData = GetCommonMonsterRowData(NowStageData->CommonMonsterType);

	// CommonMonster�� ��ȯ�Ϸ�Ǹ� Ÿ�̸Ӹ� �����Ѵ�.
	if(NowWaveMonsterCount.CommonMonsterSpawnCount == NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(CommonMonsterSpawnTimer);
		UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
		return;
		
	}
	
	// ���͸� ��ȯ�մϴ�.
	if(NowStageData !=nullptr)
	{
		// CommonMonster��ȯ
		if(NowStageData->MonsterWave.Num()!=0)
		{
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

			//Wave�� ���͸� �����ϱ� ���� ǽ���� ���͸� �����ɴϴ�.
			ACommonMonster* TmpCommonMonster = gm->ObjectPooler->GetPooledCommonMonster();
			if(TmpCommonMonster==nullptr)
			{
				UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
				return;
			}
			// ���� Ÿ������ �ʱ�ȭ�ؼ� Ȱ��ȭ���ݴϴ�.
			TmpCommonMonster->InitMonster(StageCommonMonsterData);
			TmpCommonMonster->SetActive(true);
			// ������ ��ġ�� ��ȯ�մϴ�. 
			int RandomPoint = FMath::RandRange(0,SpawnPoints.Num()-1);
			TmpCommonMonster->SetActorLocation(SpawnPoints[RandomPoint]);
			// ���� ��ȯ�� CommonMonster���� �ø��ϴ�. 
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
	// �������� ����(���̺�)�� ����ϴ�.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	// CommonMonster�� ��ȯ�Ϸ�Ǹ� Ÿ�̸Ӹ� �����Ѵ�.
	if(NowWaveMonsterCount.TowerMonsterSpawnCount == NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(TowerMonsterSpawnTimer);
		return;
	}
	

	// ������ Ÿ���� ����ϴ�.
	const FTowerMonsterData*  StageTowerMonsterData = GetTowerMonsterRowData(NowStageData->TowerMonsterType);
	
	// ���͸� ��ȯ�մϴ�.
	if(NowStageData !=nullptr)
	{
		// CommonMonster��ȯ
		if(NowStageData->MonsterWave.Num()!=0)
		{
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

			//Wave�� ���͸� �����ϱ� ���� ǽ���� ���͸� �����ɴϴ�.
			ATowerMonster* TmpTowerMonster = gm->ObjectPooler->GetPooledTowerMonster();
			if(TmpTowerMonster==nullptr)
			{
				UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
				return;
			}
			// ���� Ÿ������ �ʱ�ȭ�ؼ� Ȱ��ȭ���ݴϴ�.
			TmpTowerMonster->InitMonster(StageTowerMonsterData);
			TmpTowerMonster->SetActive(true);
			// ������ ��ġ�� ��ȯ�մϴ�. 
			int RandomPoint = FMath::RandRange(0,SpawnPoints.Num()-1);
			TmpTowerMonster->SetActorLocation(SpawnPoints[RandomPoint]);
			// ���� ��ȯ�� CommonMonster���� �ø��ϴ�. 
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
	// �������� ����(���̺�)�� ����ϴ�.
	const FGameStageRow*  NowStageData  = GetGameStateRowData(NowStage);
	// CommonMonster�� ��ȯ�Ϸ�Ǹ� Ÿ�̸Ӹ� �����Ѵ�.
	if(NowWaveMonsterCount.BossMonsterSpawnCount == NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(BossMonsterSpawnTimer);
		return;
	}
	

	// ������ Ÿ���� ����ϴ�.
	const FBossMonsterData*  StageBossMonsterData = GetBossMonsterRowData(NowStageData->BossMonsterType);
	
	// ���͸� ��ȯ�մϴ�.
	if(NowStageData !=nullptr)
	{
		// CommonMonster��ȯ
		if(NowStageData->MonsterWave.Num()!=0)
		{
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

			//Wave�� ���͸� �����ϱ� ���� ǽ���� ���͸� �����ɴϴ�.
			ABossMonster* TmpCommonMonster = gm->ObjectPooler->GetPooledBossMonster();
			if(TmpCommonMonster==nullptr)
			{
				UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
				return;
			}
			// ���� Ÿ������ �ʱ�ȭ�ؼ� Ȱ��ȭ���ݴϴ�.
			TmpCommonMonster->InitMonster(StageBossMonsterData);
			TmpCommonMonster->SetActive(true);
			// ������ ��ġ�� ��ȯ�մϴ�. 
			int RandomPoint = FMath::RandRange(0,SpawnPoints.Num()-1);
			TmpCommonMonster->SetActorLocation(SpawnPoints[RandomPoint]);
			// ���� ��ȯ�� CommonMonster���� �ø��ϴ�. 
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
	
	//UE_LOG(LogTemp, Warning,TEXT("TowerMonsterSpawnCount : %d  & NowWave: %d"),MonsterDeadCount.TowerMonsterSpawnCount ,NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount);
	// ���͸� �� ��Ҵٸ�

// 	
// 	
// 	PlayerScoreWidget->SetRemainMonsterText((NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount - MonsterDeadCount.CommonMonsterSpawnCount) +
// NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount-MonsterDeadCount.TowerMonsterSpawnCount+NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount-
// MonsterDeadCount.BossMonsterSpawnCount);
// 	 			auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
// 	 			player->PlayerScoreWidget->SetNowWaveText(NowWave,GameInstanceRef->GoalWave);
	
	RemainMonster = (NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount - MonsterDeadCount.CommonMonsterSpawnCount) +
			NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount-MonsterDeadCount.TowerMonsterSpawnCount+NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount-
			MonsterDeadCount.BossMonsterSpawnCount;
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	gm->PlayerScoreWidget->SetRemainMonsterText(RemainMonster);
	
	if(MonsterDeadCount.CommonMonsterSpawnCount == NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount &&
		MonsterDeadCount.TowerMonsterSpawnCount == NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount&&
		MonsterDeadCount.BossMonsterSpawnCount == NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount)
			
	{
	
	
		// ���̺갡 ���Ҵٸ� �������̺��
		if(NowWave < NowStageData->MonsterWave.Num())
		{
			
			NowWave+=1;
			NowWaveMonsterCount.CommonMonsterSpawnCount = 0; 
			NowWaveMonsterCount.TowerMonsterSpawnCount = 0;
			NowWaveMonsterCount.BossMonsterSpawnCount = 0;

			MonsterDeadCount.CommonMonsterSpawnCount =0;
			MonsterDeadCount.TowerMonsterSpawnCount =0;
			MonsterDeadCount.BossMonsterSpawnCount =0;

			gm->PlayerScoreWidget->SetNowWaveText(NowWave,GoalWave);
			RemainMonster = (NowStageData->MonsterWave[NowWave].CommonMonsterSpawnCount - MonsterDeadCount.CommonMonsterSpawnCount) +
		NowStageData->MonsterWave[NowWave].TowerMonsterSpawnCount-MonsterDeadCount.TowerMonsterSpawnCount+NowStageData->MonsterWave[NowWave].BossMonsterSpawnCount-
		MonsterDeadCount.BossMonsterSpawnCount;
			
			gm->PlayerScoreWidget->SetRemainMonsterText(RemainMonster);
			GetWorld()->GetTimerManager().SetTimer(CommonMonsterSpawnTimer, this, &UStageManageComponent::SpawnCommonMonster, SpawnCoolTime,true);
			
		}
		// �ƴ϶�� �������� Ŭ����
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
	//player->PlayerScoreWidget->ShowStageClearBox(true);
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

