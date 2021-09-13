// Copyright Epic Games, Inc. All Rights Reserved.


#include "RealGameModeBase.h"

#include "BossMonsterActor.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "ChooseSkillWidget.h"
#include "ItemActor.h"
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
		SaveGameInstance->FireRate = player->GetFireRate();
		SaveGameInstance->MoveSpeed = player->GetMoveSpeed();
		SaveGameInstance->BulletPower = player->GetBulletPower();
		SaveGameInstance->MaxHP = player->GetMaxHp();
		SaveGameInstance->PlayerCoin = player->GetCoin();
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
			player->SetFireRate(LoadGameInstance->FireRate);
			player->SetMoveSpeed(LoadGameInstance->MoveSpeed);
			player->SetMaxHp(LoadGameInstance->MaxHP);
			player->SetBulletPower(LoadGameInstance->BulletPower);
			player->SetPlayerCoin(LoadGameInstance->PlayerCoin);
		}
	}
}


void ARealGameModeBase::BeginPlay()
{
	StartTime = 0.0f;
	// �Ѿ� ����
	BulletPooler->Spawn();
	MonsterPooler->Spawn();
	ItemPooler->Spawn();
	Load();


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

	if (GetWorld()->GetName() == "MainLevel")
	{
		PlayerSkillChooseWidget = Cast<UChooseSkillWidget>(CreateWidget(GetWorld(), PlayerSkillChooseClass));
		if (PlayerSkillChooseClass != nullptr)
		{
			// PlayerSkillChooseWidget->Player=this;
			// PlayerRightWidget->AddToViewport();
		}

		UWorld* const World = GetWorld();
		World->GetTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn,
		                                  MonsterSpawnCoolTime);
	}
}


void ARealGameModeBase::MonsterSpawn()
{
	UWorld* const World = GetWorld();
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	FVector result = FMath::VRand();


	// ���� ��� �����ϰ� (�ּ�  ~�ִ� )
	int const randMonsterMun = FMath::RandRange(SpawnMonsterRandomNumMin, SpawnMonsterRandomNumMax);
	AMonsterActor* Monster = MonsterPooler->GetPooledMonster();
	ATowerMonsterActor* TowerMonster = MonsterPooler->GetPooledTowerMonster();
	ABossMonsterActor* BossMonster = MonsterPooler->GetPooledBossMonster();
	
	// ���� ����
	for (int i = 0; i < (MonsterSpawnNum + randMonsterMun); i++)
	{
		MonsterType = FMath::RandRange(1, 3);
		result = FMath::VRand();
		result *= FMath::RandRange(SpawnRangeMin, SpawnRangeMax);


		// �ܰ� ����
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(result.X));
		result *= FVector(1.f, 1.f, 0.f);
		result += player->GetActorLocation();
		
		switch (MonsterType)
		{
		case 1:
			Monster = MonsterPooler->GetPooledMonster();
			Monster->SetActorLocation(result);
			// ���� ��ȣ�� ������ �ʱ�ȭ�Ѵ� 
			Monster->InitMonster(MonsterType);
			Monster->SetActive(true);
			if (Monster == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
				GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
				return;
			}
			break;
		case 2:
		case 3:
			TowerMonster = MonsterPooler->GetPooledTowerMonster();
			TowerMonster->SetActorLocation(result);
			// ���� ��ȣ�� ������ �ʱ�ȭ�Ѵ� 
			TowerMonster->InitMonster(MonsterType);
			TowerMonster->SetActive(true);
			if (TowerMonster == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
				GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
				return;
			}
			break;
		case 4:
			BossMonster = MonsterPooler->GetPooledBossMonster();
			BossMonster->SetActorLocation(result);
			// ���� ��ȣ�� ������ �ʱ�ȭ�Ѵ� 
			BossMonster->InitMonster(MonsterType);
			BossMonster->SetActive(true);
			if (BossMonster == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
				GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
				return;
			}
			break;
		default:
			Monster = MonsterPooler->GetPooledMonster();
			Monster->SetActorLocation(result);
			// ���� ��ȣ�� ������ �ʱ�ȭ�Ѵ� 
			Monster->InitMonster(MonsterType);
			Monster->SetActive(true);
			if (Monster == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
				GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, false);
				return;
			}
			break;
		}
	}
	//��Ÿ�� �����ϰ� ����
	float const RandCoolTime = FMath::RandRange(SpawnCoolTimeRandomMin, SpawnCoolTimeRandomMax);
	MonsterSpawnCoolTime += RandCoolTime;
	GetWorldTimerManager().SetTimer(MonsterSpawnTimer, this, &ARealGameModeBase::MonsterSpawn, MonsterSpawnCoolTime);
	UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));
}
