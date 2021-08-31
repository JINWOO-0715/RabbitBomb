// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "ChooseSkillWidget.h" 
#include "ItemActor.h"

#include "MainPawn.h"

ARealGameModeBase::ARealGameModeBase()
{
	DefaultPawnClass = AMainPawn::StaticClass();

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

}

FMonsterRow* ARealGameModeBase::GetMonsterRowData(int rowN)
{
	FMonsterRow* MonsterRowData = MonsterData->FindRow<FMonsterRow>(
			FName(*(FString::FormatAsNumber(rowN))), FString(""));

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
	// �Ѿ� ����
	BulletPooler->Spawn();
	MonsterPooler->Spawn();



	// //���� ����
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