// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MonsterMeshComponent;
	SetActorEnableCollision(false);
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonsterMeshComponent->SetCollisionProfileName("Monster");

	AttackPatternComponent = CreateDefaultSubobject<UBulletAttackPattern>(TEXT("AttackPatternComponent"));
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

