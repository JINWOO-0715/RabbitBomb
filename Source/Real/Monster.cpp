// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "RealGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 메시
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MonsterMeshComponent;
	
	// 충돌설정
	SetActorEnableCollision(false);
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonsterMeshComponent->SetCollisionProfileName("Monster");

	//공격패턴
	AttackPatternComponent = CreateDefaultSubobject<UBulletAttackPattern>(TEXT("AttackPatternComponent"));

	// 스탯 기본설정.
	Active =false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	SetActive(true);
}

void AMonster::InitMonster(const FMonsterRow  *const mMonsterStat)
{


	
	//메시설정
	MonsterMeshComponent->SetStaticMesh(mMonsterStat->MonsterMesh);
	//총알속도
	MonsterStat.BulletSpeed = mMonsterStat->BulletSpeed;
	//공격속도
	MonsterStat.FireRate = mMonsterStat->FireRate;
	// 몬스터HP
	MonsterStat.MonsterHP =  mMonsterStat->MonsterHP;
	//총알 파워
	MonsterStat.BulletPower = mMonsterStat->BulletPower;
	//몬스터 이속
	MonsterStat.MoveSpeed = mMonsterStat->MoveSpeed;
	//
	MonsterStat.BulletLifeSpan = mMonsterStat->BulletLifeSpan;
}

void AMonster::SetActive(bool InActive)
{
	Active=InActive;
	// 충돌 off
	SetActorEnableCollision(InActive);

	//숨기기
	SetActorHiddenInGame(!InActive);

	//메시 
	MonsterMeshComponent->SetActive(InActive);

	//틱종료
	SetActorTickEnabled(InActive);

	GetWorldTimerManager().SetTimer(AttackTimer, this
								, &AMonster::ShotTimerExpired, MonsterStat.FireRate);
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::ShotTimerExpired()
{
	bCanFire = true;

}

