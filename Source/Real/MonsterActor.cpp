// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterActor.h"
#include "Bullet.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "RealGameModeBase.h"
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
	MonseterMeshComponent->SetCollisionObjectType(ECC_GameTraceChannel2);
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

// Ȱ��ȭ on/off
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

	// ���� �ӵ��� ���� �Ѿ��� �߻���. 
	GetWorldTimerManager().SetTimer(AttackTimer,this
		,&AMonsterActor::ShotTimerExpired,FireRate,InActive);
		//
		// GetWorldTimerManager().SetTimer(MovespanTimer,this
		// 	,&AMonsterActor::MoveToTarget,MovetoTagetUpdateDuration,InActive);
}
void AMonsterActor::ShotTimerExpired()
{
	bCanFire =true;
}


// �����̴� �Լ� 
void AMonsterActor::MoveToTarget()
{
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	FVector Dir = player->GetActorLocation() - this->GetActorLocation();
	Dir.Normalize();// ���⺤��
	
	const FVector Movement = Dir * MoveSpeed;// 
	FRotator NewRotation = Movement.Rotation();
	RootComponent->MoveComponent(Movement, NewRotation, true);

	
}
// Ȱ��ȭ �޴� �Լ�.
bool AMonsterActor::IsActive()
{
	return Active;
}

//Ȱ��ȭ ���� �Լ�
void AMonsterActor::Deactivate()
{
	// ���⿡ Ÿ�̸� ���Ḧ �ִ´�. 
	SetActive(false);
	MonseterMeshComponent->Deactivate();
	
}


// ������ �޴� �Լ� �������̵� ���
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

// �ѽ�� �Լ� 
void AMonsterActor::FireShot()
{
	if(bCanFire)
	{
		bCanFire = false;// ����
		
		UWorld* const World = GetWorld();
		 ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		 ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
		if(monsterBullet && World)
		{
			monsterBullet->SetOwnerActor(this);
			FVector Dir = GetActorLocation();
			monsterBullet->SetActorLocation(Dir);
			// monsterBullet->SetActorRotation(FRotator(90.f,-90.f,0.f));
			monsterBullet->SetLifeSpan();
			monsterBullet->SetActive(true);
		}	
		//
		// AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
		// Ÿ�̸� �۵�
		//World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);

	}
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
	//if ���� ������ �������� �ƴѰ�!
	if (Active)
	{
		MoveToTarget();
		
		FireShot();
	}
}

