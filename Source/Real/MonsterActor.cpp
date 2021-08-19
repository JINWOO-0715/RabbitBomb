// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterActor.h"
#include "Bullet.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"


#include "GameplayTagsModule.h"
#include "GameplayTagsSettings.h"
#include "GameplayTags.h"
#include "GameplayTagsManager.h"
#include "Sound/SoundBase.h"



// Sets default values
AMonsterActor::AMonsterActor()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonseterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MonseterMeshComponent;
	SetActorEnableCollision(false);
	//MonseterMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MonseterMeshComponent->SetStaticMesh(MeshAsset.Object);

	MonseterMeshComponent->SetGenerateOverlapEvents(false);
    Tags.Add("Monster");


    //OnTakeAnyDamage.AddDynamic(this, &AMonsterActor::TakeDamage);
}

// ���� �ֱ� �ܺο��� ���������ϰ� ����
void AMonsterActor::SetLifeSpan(float InLifespan)
{
	Lifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer,this
		,&AMonsterActor::Deactivate,Lifespan,false);

}

// Ȱ��ȭ��  
void AMonsterActor::SetActive(bool InActive)
{
	
		Active =InActive;
	// �浹 off
		SetActorEnableCollision(InActive);
	//�����
		SetActorHiddenInGame(!InActive);
	//�޽� ����� �̰� �ʿ��Ѱ�
		//MonseterMeshComponent->SetActive(InActive);
	//ƽ����
		SetActorTickEnabled(InActive);
		//
		// GetWorldTimerManager().SetTimer(MovespanTimer,this
		// 	,&AMonsterActor::MoveToTarget,MovetoTagetUpdateDuration,InActive);
}

// �׽�Ʈ �� ��ġ�ų� �����. -> �̰� ����ȭ �� ����� ���°ǰ�!? 
void AMonsterActor::MoveToTarget()
{
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	FVector Dir = player->GetActorLocation() - this->GetActorLocation();
	Dir.Normalize();// ���⺤��
	
	const FVector Movement = Dir * MoveSpeed;// 
	FRotator NewRotation = Movement.Rotation();
	RootComponent->MoveComponent(Movement, NewRotation, true);

	
}

bool AMonsterActor::IsActive()
{
	return Active;
}
void AMonsterActor::Deactivate()
{
	// ���⿡ Ÿ�̸� ���Ḧ �ִ´�. 
	SetActive(false);
	MonseterMeshComponent->Deactivate();
	
}


// �������̵� ���
float AMonsterActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	MonsterHP-=Damage;
	if (MonsterHP<0.f)
	{
		Deactivate();
	}

	return Damage;
}

//
// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
// MonsterHP -= Damage;
// if (MonsterHP < 0)
// {
// 	Destroy();


//// Called when the game starts or when spawned
//void AMonsterActor::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
void AMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Active)
	{
		MoveToTarget();
		
	}
}

