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
//#include "Systems/MovieSceneQuaternionInterpolationRotationSystem.h"


// Sets default values
AMonsterActor::AMonsterActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �޽�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonseterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MonseterMeshComponent;
	SetActorEnableCollision(false);
	MonseterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonseterMeshComponent->SetCollisionProfileName("Monster");




	//�浹������ �ٽ� �غ���
	//MonseterMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	
	//MonseterMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	//MonseterMeshComponent->SetCollisionObjectType(ECC_GameTraceChannel2);
	MonseterMeshComponent->SetGenerateOverlapEvents(false);
	Tags.Add("Monster");


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
	MonseterMeshComponent->SetActive(InActive);

	//ƽ����
	SetActorTickEnabled(InActive);


	
	// ���� �ӵ��� ���� �Ѿ��� �߻���. 
	GetWorldTimerManager().SetTimer(AttackTimer, this
	                                , &AMonsterActor::ShotTimerExpired, FireRate, InActive);
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
	MonseterMeshComponent->Deactivate();
}


// ������ �޴� �Լ� �������̵� ���
float AMonsterActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	MonsterHP -= Damage;
	if (MonsterHP < 0.f)
	{
		Deactivate();
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
			// Dir.Normalize(); // ����
			//
			// const FVector Movement = Dir * BulletSpeed; //
			// // �������ִ� ���� ����?
			// monsterBullet->SetOwnerActor(this);
			// // �������ִ� �Ѿ���ġ
			// monsterBullet->SetActorLocation(GetActorLocation());
			// //�Ѿ� �ӵ�
			// monsterBullet->SetVelocity(Movement);
			// // �˾Ƽ� ��������ϰ�
			// monsterBullet->SetLifeSpan();
			// // Ȱ��ȭ��Ų��.
			// monsterBullet->SetActive(true);

			// 4�������� �߻�
			for(int i = 0 ; i<5;i++)
			{
				monsterBullet = gm->BulletPooler->GetPooledBullet();
				const FVector randomV(FMath::RandRange(-0.5f, 0.5f),FMath::RandRange(0.f, 2.f),0.f);
				Dir+=randomV;
				Dir.Normalize();
				const FVector FMovement = Dir * BulletSpeed; //
				// �������ִ� ���� ����?
				monsterBullet->SetOwnerActor(this);
				// �������ִ� �Ѿ���ġ
				monsterBullet->SetActorLocation(GetActorLocation());
				//�Ѿ� �ӵ�
				monsterBullet->SetVelocity(FMovement);
				// �˾Ƽ� ��������ϰ�
				monsterBullet->SetLifeSpan();
				// Ȱ��ȭ��Ų��.
				monsterBullet->SetActive(true);
			}
		
		}
		// 
		float angle = 36;


		
		//
		// AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

		// Ÿ�̸� �۵�
		//World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);
	}
}

void AMonsterActor::InitMonster(int dataRowN)
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	FMonsterRow* MonsterData = gm->GetMonsterRowData(dataRowN);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(MonsterData->FireRate));

	BulletSpeed=MonsterData->BulletSpeed;
	FireRate=MonsterData->FireRate;
	Lifespan=MonsterData->Lifespan;
	MonsterHP=MonsterData->MonsterHP;
	MoveSpeed=MonsterData->BulletSpeed;

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
		const AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // ����

		const FVector Movement = Dir * MoveSpeed *DeltaTime; //
		if (Movement.SizeSquared() > 0.0f)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
			const FRotator NewRotation = Movement.Rotation();
			FHitResult Hit(1.f);
			RootComponent->MoveComponent(Movement, NewRotation, true , &Hit);
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
	
			//MoveToTarget();
		}
		FireShot();
	}
}
