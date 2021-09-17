// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterActor.h"

//#include <concrt.h>

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
//#include "Systems/MovieSceneQuaternionInterpolationRotationSystem.h"


// Sets default values
AMonsterActor::AMonsterActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �޽�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MonsterMeshComponent;
	SetActorEnableCollision(false);
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonsterMeshComponent->SetCollisionProfileName("Monster");


	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HitedMTAsset(
		TEXT("/Game/Mesh/MonsterHitedMT.MonsterHitedMT"));
	//MonsterHitedMT = CreateDefaultSubobject<UMaterialInterface>(TEXT("Mesh"));
	MonsterHitedMT = HitedMTAsset.Object;


	//�浹������ �ٽ� �غ���
	//MonseterMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	//MonseterMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	//MonseterMeshComponent->SetCollisionObjectType(ECC_GameTraceChannel2);
	MonsterMeshComponent->SetGenerateOverlapEvents(false);
	Tags.Add("Monster");

	bCanFire = true;
	//OnTakeAnyDamage.AddDynamic(this, &AMonsterActor::TakeDamage);
}

// ���� �ֱ� �ܺο��� ���������ϰ� ����
void AMonsterActor::SetLifeSpan(float InLifespan)
{
	Lifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer, this
	                                , &AMonsterActor::Deactivate, Lifespan, false);
}

// Ȱ��ȭ on/off
void AMonsterActor::SetActive(bool InActive)
{
	Active = InActive;
	// �浹 off
	SetActorEnableCollision(InActive);

	//�����
	SetActorHiddenInGame(!InActive);

	//�޽� 
	MonsterMeshComponent->SetActive(InActive);

	//ƽ����
	SetActorTickEnabled(InActive);


	// ���� �ӵ��� ���� �Ѿ��� �߻���. 
	GetWorldTimerManager().SetTimer(AttackTimer, this
	                                , &AMonsterActor::ShotTimerExpired, FireRate);
	//
	// GetWorldTimerManager().SetTimer(MovespanTimer,this
	// 	,&AMonsterActor::MoveToTarget,MovetoTagetUpdateDuration,InActive);
}


void AMonsterActor::ShotTimerExpired()
{
	bCanFire = true;
}


// �����̴� �Լ� 
void AMonsterActor::MoveToTarget()
{
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector Dir = player->GetActorLocation() - this->GetActorLocation();
	Dir.Normalize(); // ����

	const FVector Movement = Dir * MoveSpeed; //

	FRotator NewRotation = Movement.Rotation();
	//FTransform d (Movement,NewRotation,NULL;
	SetActorRotation(NewRotation);
	//AddActorWorldOffset(Movement,true,nullptr);
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
	MonsterMeshComponent->Deactivate();
}


// ������ �޴� �Լ� �������̵� ���
float AMonsterActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	MonsterHP -= Damage;
	ChangeHitedMTTimer();
	if (MonsterHP < 0.f)
	{
		int rand = FMath::RandRange(0, 1);
		ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		if (rand == 0)
		{
			
			AItemActor* Item = gm->ItemPooler->GetPooledUItem();
			Item->SetActorLocation(GetActorLocation());
			Item->SetActive(true);
		}
		// ��ġ���� ȹ�� Ȯ�� 40%
		Deactivate();
		gm->DecreaseCommomMonsterCount();
	}

	return Damage;
}

// �ѽ�� �Լ� 
void AMonsterActor::FireShot()
{
	if (bCanFire)
	{
		bCanFire = false; // ����


		// �׳� 1�� �÷��̾� �������� �߻�.
		UWorld* const World = GetWorld();
		ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
		if (monsterBullet && World)
		{
			AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			FVector Dir = player->GetActorLocation() - this->GetActorLocation();
			Dir.Normalize(); // ����

			const FVector Movement = Dir * BulletSpeed; //
			// �������ִ� ���� ����?
			monsterBullet->SetOwnerActor(this);
			// �������ִ� �Ѿ���ġ
			monsterBullet->SetActorLocation(GetActorLocation());
			// �Ѿ� �ӵ�
			monsterBullet->SetVelocity(Movement);
			// �˾Ƽ� ��������ϰ�
			monsterBullet->SetLifeSpan(BulletLifeSpan);
			// Ȱ��ȭ��Ų��.
			monsterBullet->SetActive(true);
		}

		World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);
	}
}

void AMonsterActor::InitMonster(int dataRowN)
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	
	FMonsterRow* MonsterData = gm->GetMonsterRowData(dataRowN);
	;
	
	
	MonsterMeshComponent->SetStaticMesh(MonsterData->MonsterMesh);
	BulletSpeed = MonsterData->BulletSpeed;
	FireRate = MonsterData->FireRate *gm->GoalGameStage->FireRateUPCount;
	Lifespan = MonsterData->Lifespan;
	float const time = GetWorld()->GetAudioTimeSeconds();
	MonsterHP =  MonsterData->MonsterHP*gm->GoalGameStage->HpUPCount;
	BulletPower = MonsterData->BulletPower*gm->GoalGameStage->BulletPowerUPCount;
	MoveSpeed = MonsterData->MoveSpeed;
	BulletLifeSpan = MonsterData->BulletLifeSpan;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(MonsterData->FireRate));
	//0.0008*x*x+100;
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

void AMonsterActor::SetStunMonster(float mStunTime)
{
	// ���ϻ��·� �ٲ۴�
	isStun = true;
	// 3���� �������
	GetWorldTimerManager().SetTimer(StunTimer, this
	                                , &AMonsterActor::StunMonster, mStunTime, false);
}

void AMonsterActor::StunMonster()
{
	isStun = false;
}

void AMonsterActor::ChangeHitedMTTimer()
{
	UMaterialInterface* temp = MonsterMeshComponent->GetMaterial(2);

	MonsterMeshComponent->SetMaterial(2, MonsterHitedMT);
	MonsterHitedMT = temp;
	MonsterMeshComponent->SetVectorParameterValueOnMaterials(FName("Color"), FVector(1.f, 0.f, 0.f));

	GetWorldTimerManager().SetTimer(MTChangeTimer, this
	                                , &AMonsterActor::ChangeHitMT, 0.2, false);
}

void AMonsterActor::ChangeHitMT()
{
	UMaterialInterface* temp = MonsterMeshComponent->GetMaterial(2);

	MonsterMeshComponent->SetMaterial(2, MonsterHitedMT);
	MonsterMeshComponent->SetVectorParameterValueOnMaterials(FName("Color"), FVector(0.f, 0.f, 1.f));
	MonsterHitedMT = temp;
	// ���󺹱ͽ�Ų��.	
}

// Called every frame
void AMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active && !isStun)
	{
		const AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // ����

		const FVector Movement = Dir * MoveSpeed * DeltaTime; //
		if (Movement.SizeSquared() > 0.0f)
		{
			if (FVector::Dist(GetActorLocation(), player->GetActorLocation()) > 800)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
				const FRotator NewRotation = FRotator(Movement.Rotation().Pitch, Movement.Rotation().Yaw, 0.0f);

				FHitResult Hit(1.f);
				RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
				AddActorWorldOffset(Movement, true, nullptr);

				if (Hit.IsValidBlockingHit())
				{
					const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
					const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
					RootComponent->MoveComponent(Deflection, NewRotation, true);
				}
				//FTransform d (Movement,NewRotation,NULL;
				//SetActorRotation(NewRotation);
				//AddActorWorldOffset(Movement,true,nullptr);
			}
			//MoveToTarget();
		}
		FireShot();
	}
}
