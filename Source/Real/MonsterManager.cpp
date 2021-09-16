// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterManager.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterDataTable.h"
#include "Components/BoxComponent.h"
#include "RealGameModeBase.h"

#include "GameFramework/Pawn.h"

// Sets default values
AMonsterManager::AMonsterManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnVolume"));

	RootComponent = SpawnVolume;
	//ObjectPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPoller"));
	//
	//������ ���̺�.
	
}

// Called when the game starts or when spawned
void AMonsterManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
}


// �����Ҽ��ְ� ������ �ʰ� �˾ƾ��ϴ°� �ƴϳ�!

void AMonsterManager::Spawn()
{
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	AMonsterActor* Monster = gm->MonsterPooler->GetPooledMonster();


	// ���Ͱ� ���׾���
	if (NowMosterCount.eBossMonster < 1 && NowMosterCount.eCommomMonster < 1 && NowMosterCount.eTowerMonster < 1)
	{
		if(NowWave < gm->GetGoalWave())
		{
			NowWave++;
			
		}
		else
		{
			gm->ChangeStage();
		}
		 // �̰� �Լ��� ����
	}
	if(NowMosterCount.eCommomMonster < gm->GetGoalCommonMonsterCount())
	{
		if (Monster == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
			return;
		}
		// ���� ��ġ
		Monster->SetActorLocation(SpawnLocation[0]);
		//���� ����
		Monster->InitMonster(1);
		// Ȱ��ȭ ����
		Monster->SetActive(true);
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
		UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));
		NowMosterCount.eCommomMonster++;

	}
	// if(���� �� ���׾����� ������)
	// {
	//		gm->stage levelUp 
	// }
	// if( �� common < gm�� goalcommon����)
	// { 
	//	�Ϲݸ� ���� (��ġ�� ���� ��ȸ��)	 
	//
	//  // �̷������� Ƽ�� / ����/ �ϴ� �Ѵ�.!
	//  }
	// 
	//

	
	

	// 

	//��ġ �����ͼ� �� �ѹ��� ����!
	//
	// if(gm->isSpawnAble())
	// {
	// 	//�����ϴٸ� �����ض�! �������϶��!
	// 	// �׳� �ʰ� ������������ �˾Ƽ���
	// 	// �����Ҳ�����
	// 	// �״��� ��������
	// 	// �״��� ���׾����� stage ��������
	// 	// �ݺ���
	// 	if (Monster == nullptr)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
	// 		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
	// 		return;
	// 	}
	//
	// 	Monster->SetActorLocation(SpawnLocation[0]);
	// 	gm->UpCommomMonsterCount();
	// 	Monster->InitMonster(MonsterNum);
	// 	Monster->SetActive(true);
	// 	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
	// 	UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));
	//
	// }
		

}

// Called every frame
void AMonsterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
