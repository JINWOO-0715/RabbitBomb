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

	// 메시
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterBaseMesh.MonsterBaseMesh"));
	MonseterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MonseterMeshComponent;
	SetActorEnableCollision(false);
	MonseterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonseterMeshComponent->SetCollisionProfileName("Monster");




	//충돌에대해 다시 해보기
	//MonseterMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	
	//MonseterMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	//MonseterMeshComponent->SetCollisionObjectType(ECC_GameTraceChannel2);
	MonseterMeshComponent->SetGenerateOverlapEvents(false);
	Tags.Add("Monster");


	//OnTakeAnyDamage.AddDynamic(this, &AMonsterActor::TakeDamage);
}

// 생명 주기 외부에서 설정가능하게 제작
void AMonsterActor::SetLifeSpan(float InLifespan)
{
	Lifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer, this
	                                , &AMonsterActor::Deactivate, Lifespan, false);
}

// 활성화 on/off
void AMonsterActor::SetActive(bool InActive)
{
	Active = InActive;
	// 충돌 off
	SetActorEnableCollision(InActive);

	//숨기기
	SetActorHiddenInGame(!InActive);

	//메시 
	MonseterMeshComponent->SetActive(InActive);

	//틱종료
	SetActorTickEnabled(InActive);


	
	// 공격 속도에 따라 총알을 발사함. 
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


// 움직이는 함수 
void AMonsterActor::MoveToTarget()
{
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector Dir = player->GetActorLocation() - this->GetActorLocation();
	Dir.Normalize(); // 벡터

	const FVector Movement = Dir * MoveSpeed; //

	FRotator NewRotation = Movement.Rotation();
	//FTransform d (Movement,NewRotation,NULL;
	SetActorRotation(NewRotation);
	//AddActorWorldOffset(Movement,true,nullptr);
	RootComponent->MoveComponent(Movement, NewRotation, true);
}

// 활성화 받는 함수.
bool AMonsterActor::IsActive()
{
	return Active;
}

//활성화 종료 함수
void AMonsterActor::Deactivate()
{
	// 여기에 타이머 종료를 넣는다. 
	SetActive(false);
	MonseterMeshComponent->Deactivate();
}


// 데미지 받는 함수 오버라이드 사용
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

// 총쏘는 함수 
void AMonsterActor::FireShot()
{
	if (bCanFire)
	{
		bCanFire = false; // 끊고


		// 그냥 1발 플레이어 방향으로 발사.
		UWorld* const World = GetWorld();
		ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
		if (monsterBullet && World)
		{
			AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			FVector Dir = player->GetActorLocation() - this->GetActorLocation();
			// Dir.Normalize(); // 벡터
			//
			// const FVector Movement = Dir * BulletSpeed; //
			// // 가지고있는 액터 누구?
			// monsterBullet->SetOwnerActor(this);
			// // 가지고있는 총알위치
			// monsterBullet->SetActorLocation(GetActorLocation());
			// //총알 속도
			// monsterBullet->SetVelocity(Movement);
			// // 알아서 살아지게하고
			// monsterBullet->SetLifeSpan();
			// // 활성화시킨다.
			// monsterBullet->SetActive(true);

			// 4방향으로 발사
			for(int i = 0 ; i<5;i++)
			{
				monsterBullet = gm->BulletPooler->GetPooledBullet();
				const FVector randomV(FMath::RandRange(-0.5f, 0.5f),FMath::RandRange(0.f, 2.f),0.f);
				Dir+=randomV;
				Dir.Normalize();
				const FVector FMovement = Dir * BulletSpeed; //
				// 가지고있는 액터 누구?
				monsterBullet->SetOwnerActor(this);
				// 가지고있는 총알위치
				monsterBullet->SetActorLocation(GetActorLocation());
				//총알 속도
				monsterBullet->SetVelocity(FMovement);
				// 알아서 살아지게하고
				monsterBullet->SetLifeSpan();
				// 활성화시킨다.
				monsterBullet->SetActive(true);
			}
		
		}
		// 
		float angle = 36;


		
		//
		// AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

		// 타이머 작동
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
	//if 문을 지워도 괜찮은거 아닌가!
	if (Active)
	{
		const AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // 벡터

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
