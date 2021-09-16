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
	//데이터 테이블.
	
}

// Called when the game starts or when spawned
void AMonsterManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
}


// 스폰할수있고 없음은 너가 알아야하는거 아니냐!

void AMonsterManager::Spawn()
{
	UWorld* const World = GetWorld();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	AMonsterActor* Monster = gm->MonsterPooler->GetPooledMonster();


	// 몬스터가 다죽었다
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
		 // 이거 함수로 ㄱㄱ
	}
	if(NowMosterCount.eCommomMonster < gm->GetGoalCommonMonsterCount())
	{
		if (Monster == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn"));
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
			return;
		}
		// 스폰 위치
		Monster->SetActorLocation(SpawnLocation[0]);
		//몬스터 종류
		Monster->InitMonster(1);
		// 활성화 ㄱㄱ
		Monster->SetActive(true);
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AMonsterManager::Spawn, SpawnCooldown, false);
		UE_LOG(LogTemp, Warning, TEXT("Monster spawn"));
		NowMosterCount.eCommomMonster++;

	}
	// if(몬스터 가 다죽었으면 레벨업)
	// {
	//		gm->stage levelUp 
	// }
	// if( 내 common < gm의 goalcommon보다)
	// { 
	//	일반몹 스폰 (위치는 벡터 순회로)	 
	//
	//  // 이런식으로 티워 / 보스/ 싹다 한다.!
	//  }
	// 
	//

	
	

	// 

	//위치 가져와서 쭉 한번에 스폰!
	//
	// if(gm->isSpawnAble())
	// {
	// 	//가능하다면 스폰해라! 뭘스폰하라고!
	// 	// 그냥 너가 스폰가능한지 알아서봐
	// 	// 스폰할꺼면해
	// 	// 그다음 수관리해
	// 	// 그다음 다죽었으면 stage 레벨업해
	// 	// 반복해
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
