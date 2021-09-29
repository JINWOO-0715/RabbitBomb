// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterActor.h"

//#include <concrt.h>

#include "Bullet.h"
#include "CoinItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "RealGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

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
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MonsterMeshComponent;
	SetActorEnableCollision(false);
	MonsterMeshComponent->SetStaticMesh(MeshAsset.Object);
	MonsterMeshComponent->SetCollisionProfileName("Monster");


	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HitedMTAsset(
		TEXT("/Game/Mesh/MonsterHitedMT.MonsterHitedMT"));
	//MonsterHitedMT = CreateDefaultSubobject<UMaterialInterface>(TEXT("Mesh"));
	MonsterHitedMT = HitedMTAsset.Object;

	static ConstructorHelpers::FObjectFinder<UPaperSprite> ImogeAsset(
		TEXT("/Game/Mesh/Sprite/Dead"));

	Imoge = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Dead"));
	Imoge->SetupAttachment(RootComponent);
	if(ImogeAsset.Object)
	{
		Imoge->SetSprite(ImogeAsset.Object);
		Imoge->SetRelativeLocation(FVector(0.f,0.f,260.f));
		Imoge->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
		Imoge->SetRelativeScale3D(FVector(5.0f,5.f,5.f));
	}


	//충돌에대해 다시 해보기
	//MonseterMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	//MonseterMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	//MonseterMeshComponent->SetCollisionObjectType(ECC_GameTraceChannel2);
	MonsterMeshComponent->SetGenerateOverlapEvents(false);
	Tags.Add("Monster");

	bCanFire = true;
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
	MonsterMeshComponent->SetActive(InActive);

	//틱종료
	SetActorTickEnabled(InActive);


	// 공격 속도에 따라 총알을 발사함. 
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
	MonsterMeshComponent->Deactivate();
}


// 데미지 받는 함수 오버라이드 사용
float AMonsterActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	//float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float Damage =DamageAmount;
	MonsterHP -= Damage;
	ChangeHitedMTTimer();
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	
	if (MonsterHP < 0.f)
	{
		UGameplayStatics::PlaySound2D(this, gm->MonsterDeadSound );
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->DeadParticle, GetActorLocation(),FRotator(0.f,0.f,0.f),FVector(3.f,3.f,3.f));

		AMainPawn* player=Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		player->PlayerScoreWidget->DereaseMonsterText();
		
		int rand = FMath::RandRange(0, 1);
		
		if (rand == 0)
		{
			
			AItemActor* Item = gm->ItemPooler->GetPooledUItem();
			Item->SetActorLocation(GetActorLocation());
			Item->SetActive(true);
		}
		
		rand = FMath::RandRange(0, 1);
		
		if (rand == 0)
		{
			
			ACoinItem* Coin = gm->ItemPooler->GetPooledCoinItem();
			
			Coin->SetActorLocation(GetActorLocation()+FVector(50.f,0.f,0.f));
			Coin->SetActive(true);
		}
		// 경치구슬 획득 확률 40%
		Deactivate();
		gm->DecreaseCommomMonsterCount();
	}

	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->HitedParticle, GetActorLocation(),FRotator(0.f,0.f,0.f),FVector(3.f,3.f,3.f));
		UGameplayStatics::PlaySound2D(this, gm->MonsterHitSound);
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
			Dir.Normalize(); // 벡터

			const FVector Movement = Dir * BulletSpeed; //
			// 가지고있는 액터 누구?
			monsterBullet->SetOwnerActor(this);
			// 가지고있는 총알위치
			monsterBullet->SetActorLocation(GetActorLocation());
			// 총알 속도
			monsterBullet->SetVelocity(Movement);
			// 알아서 살아지게하고
			monsterBullet->SetLifeSpan(BulletLifeSpan);
			// 활성화시킨다.
			monsterBullet->SetActive(true);
		}

		World->GetTimerManager().SetTimer(AttackTimer, this, &AMonsterActor::ShotTimerExpired, FireRate);
	}
}

void AMonsterActor::InitMonster(int dataRowN)
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	
	FMonsterRow* MonsterData = gm->GetMonsterRowData(dataRowN);
	
	
	ChangeHitMT();
	MonsterMeshComponent->SetStaticMesh(MonsterData->MonsterMesh);
	BulletSpeed = MonsterData->BulletSpeed;
	FireRate = MonsterData->FireRate *gm->GoalGameStage->FireRateUPCount;
	Lifespan = MonsterData->Lifespan;
	float const time = GetWorld()->GetAudioTimeSeconds();
	MonsterHP =  MonsterData->MonsterHP*gm->GoalGameStage->HpUPCount;
	BulletPower = MonsterData->BulletPower*gm->GoalGameStage->BulletPowerUPCount;
	MoveSpeed = MonsterData->MoveSpeed;
	BulletLifeSpan = MonsterData->BulletLifeSpan;
	
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
	// 스턴상태로 바꾼다
	isStun = true;
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->DeadParticle2, GetActorLocation());
	// 3초후 원래대로
	GetWorldTimerManager().SetTimer(StunTimer, this
	                                , &AMonsterActor::StunMonster, mStunTime, false);
}

void AMonsterActor::StunMonster()
{
	isStun = false;
}

void AMonsterActor::ChangeHitedMTTimer()
{
	//UMaterialInterface* temp = MonsterMeshComponent->GetMaterial(2);

	//MonsterMeshComponent->SetMaterial(2, MonsterHitedMT);
	//MonsterHitedMT = temp;
	MonsterMeshComponent->SetVectorParameterValueOnMaterials(FName("Color"), FVector(1.f, 0.f, 0.f));

	GetWorldTimerManager().SetTimer(MTChangeTimer, this
	                                , &AMonsterActor::ChangeHitMT, 0.2, false);
}

void AMonsterActor::ChangeHitMT()
{
	//UMaterialInterface* temp = MonsterMeshComponent->GetMaterial(2);

	//MonsterMeshComponent->SetMaterial(2, MonsterHitedMT);
	MonsterMeshComponent->SetVectorParameterValueOnMaterials(FName("Color"), FVector(0.994792f, 0.f, 0.146117f));
	//MonsterHitedMT = temp;
	// 원상복귀시킨다.	
}

// Called every frame
void AMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active && !isStun)
	{
		const AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize(); // 벡터

		const FVector Movement = Dir * MoveSpeed * DeltaTime; //
		if (Movement.SizeSquared() > 0.0f)
		{
			if (FVector::Dist(GetActorLocation(), player->GetActorLocation()) > 500)
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
