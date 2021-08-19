// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
ABulletManager::ABulletManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("spawnVolume"));

	RootComponent=SpawnVolume;
	ObjectPooler = CreateDefaultSubobject<UBulletPoolComopnent>(TEXT("ObjectPoller"));
	
}

// Called when the game starts or when spawned
void ABulletManager::BeginPlay()
{
	Super::BeginPlay();

	// 소환술!
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer,this	,&ABulletManager::Spawn,SpawnCooldown,false);
}

void ABulletManager::Spawn()
{
	//플레이어 캐릭터 위치 
	AActor* myActor = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	// 꺼내오는거 .
	ABullet* PoolableActor = ObjectPooler->GetPooledBullet();
	if(PoolableActor == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Cannot spawn"));
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer,this,&ABulletManager::Spawn ,SpawnCooldown,false);
		return;
	}
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	FVector Dir = GetActorLocation();
	//	FRotator.Dir.Rotation();
	PoolableActor->SetActorLocation(Dir);
	PoolableActor->SetActorRotation(FRotator(90.f,-90.f,0.f));
	PoolableActor->SetLifeSpan(LifeSpan);
	PoolableActor->SetActive(true);
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer,this,&ABulletManager::Spawn ,SpawnCooldown,true);
	UE_LOG(LogTemp,Warning,TEXT("Bllet spawn"));
}

// Called every frame
void ABulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

