// Fill out your copyright notice in the Description page of Project Settings.


#include "StageManageComponent.h"
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

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterDataAsset(TEXT("/Game/BP/CommonMonsterDT"));
	if (MonsterDataAsset.Succeeded())
	{
		CommonMonsterData = MonsterDataAsset.Object;
	}
	NowWave=0;
	NowWaveMonsterType.CommonMonsterSpawnCount = 0; 
	NowWaveMonsterType.TowerMonsterSpawnCount = 0;
	NowWaveMonsterType.BossMonsterSpawnCount =  0;
}


FGameStageRow* UStageManageComponent::GetGameStateRowData(int rowN=1) const
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

FCommonMonsterData* UStageManageComponent::GetCommonMonsterRowData(int rowN=1) const
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

void UStageManageComponent::StageStart(int StageNum)
{
	const FGameStageRow*  NowStage  = GetGameStateRowData(StageNum);

	// 몬스터의 타입을 얻습니다.
	const FCommonMonsterData*  StageCommonMonsterData = GetCommonMonsterRowData(NowStage->CommonMonsterType);
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	


	NowWave=1;
	NowWaveMonsterType.CommonMonsterSpawnCount = 0; 
	NowWaveMonsterType.TowerMonsterSpawnCount = 0;
	NowWaveMonsterType.BossMonsterSpawnCount =  0;
	
	if(NowStage !=nullptr)
	{
		// CommonMonster소환
		if(NowStage->MonsterWave.Num()!=0)
		{
			for(int i = 0 ; i < NowStage->MonsterWave[NowWave].CommonMonsterSpawnCount;i++)
			{
				//타입의 몬스터를 적용하기 위해 퓰링된 몬스터를 가져옵니다.
				ACommonMonster* TmpCommonMonster = gm->MonsterPooler->GetPooledCommonMonster();
				if(TmpCommonMonster==nullptr)
				{
					UE_LOG(LogTemp, Warning,TEXT("CommonMonster is Not Valid"));
					return;
				}
				
				// 몬스터 타입으로 초기화해서 활성화해줍니다.
				TmpCommonMonster->InitMonster(StageCommonMonsterData);
				TmpCommonMonster->SetActive(true);
				TmpCommonMonster->SetActorLocation(FVector(0.0f,370.f,150.f));
				NowWaveMonsterType.CommonMonsterSpawnCount++;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning,TEXT("NowStage->MonsterWave.Num() is Empty!!!"));
		}
		
	}

	


	
	
}

void UStageManageComponent::IsClearWave()
{
	if(NowWaveMonsterType.BossMonsterSpawnCount<1)
	{
		ClearWave();
	}
		
}

void UStageManageComponent::ClearWave()
{
	NowWave+=1;
	NowWaveMonsterType.CommonMonsterSpawnCount = 0; 
	NowWaveMonsterType.TowerMonsterSpawnCount = 0;
	NowWaveMonsterType.BossMonsterSpawnCount = 0;
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

