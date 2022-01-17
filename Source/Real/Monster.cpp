// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "RealGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �޽�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MonsterMeshComponent;
	
	// �浹����
	SetActorEnableCollision(false);
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonsterMeshComponent->SetCollisionProfileName("Monster");

	//��������
	AttackPatternComponent = CreateDefaultSubobject<UBulletAttackPattern>(TEXT("AttackPatternComponent"));

	// ���� �⺻����.
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


	
	//�޽ü���
	MonsterMeshComponent->SetStaticMesh(mMonsterStat->MonsterMesh);
	//�Ѿ˼ӵ�
	MonsterStat.BulletSpeed = mMonsterStat->BulletSpeed;
	//���ݼӵ�
	MonsterStat.FireRate = mMonsterStat->FireRate;
	// ����HP
	MonsterStat.MonsterHP =  mMonsterStat->MonsterHP;
	//�Ѿ� �Ŀ�
	MonsterStat.BulletPower = mMonsterStat->BulletPower;
	//���� �̼�
	MonsterStat.MoveSpeed = mMonsterStat->MoveSpeed;
	//
	MonsterStat.BulletLifeSpan = mMonsterStat->BulletLifeSpan;
}

void AMonster::SetActive(bool InActive)
{
	Active=InActive;
	// �浹 off
	SetActorEnableCollision(InActive);

	//�����
	SetActorHiddenInGame(!InActive);

	//�޽� 
	MonsterMeshComponent->SetActive(InActive);

	//ƽ����
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

