// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Monster.h"
#include "Engine/StaticMesh.h"




// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//PrimaryActorTick.bCanEverTick = true;
		// 생성자에서만 설정 절대 틱을 안쓴다 = false
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Game/Mesh/BulletMesh.BulletMesh"));
	
	// Create mesh component for the projectile sphere
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));


		
	BulletMesh->SetStaticMesh(BulletMeshAsset.Object);
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetGenerateOverlapEvents(false);
	BulletMesh->BodyInstance.SetCollisionProfileName("Projectile");
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);		// set up a notification for when this component hits something
	BulletMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	BulletMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//BulletMesh->SetCollisionProfileName("Bullet");
	// 기본 충돌 셋팅
	BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic,ECollisionResponse::ECR_Block);
	//BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2,ECollisionResponse::ECR_Block);
	//BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Block);
	//BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECollisionResponse::ECR_Block);
	RootComponent = BulletMesh;


	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	BulletMovement->UpdatedComponent = BulletMesh;
	BulletMovement->InitialSpeed = 3000.f;
	BulletMovement->MaxSpeed = 3000.f;
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->bShouldBounce = false;
	BulletMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		// 히트하면 처리 여기서 
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());			

		
	}
	
	// 몬스터 처리 
	if (OtherActor->ActorHasTag("Monster"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, BulletDamage,nullptr, nullptr, nullptr);
		if(BulletType==FName("Ice"))
		{

			// AMonsterActor* TempMonster = Cast<AMonsterActor>(OtherActor);
			// TempMonster->SetStunMonster(2.f);
		}

	}
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, BulletDamage,nullptr, nullptr, nullptr);
	}
	// 재사용
	Deactivate();
}

// 생명 주기 외부에서 설정가능하게 제작
void ABullet::SetLifeSpan(float InLifespan)
{
	Lifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer,this
		,&ABullet::Deactivate,Lifespan,false);
	

}
void ABullet::SetActive(bool InActive)
{
	Active =InActive;
	// 충돌off
	SetActorEnableCollision(InActive);
	// 숨기기
	SetActorHiddenInGame(!InActive);
	// 메시지우기
	//BulletMesh->SetActive(InActive);
	// 틱종료
	SetActorTickEnabled(InActive);
	
	BulletMovement->SetActive(InActive);

}

void ABullet::SetOwnerActor(const AActor* ActorClass)
{
	const AActor *OwnerActor = ActorClass;
	
	if(OwnerActor)
	{
		if (OwnerActor->ActorHasTag("Monster"))
		{
			// 총알 설정.
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
			
			// mesh를 2개가지고 바꿔가면서 쓴다.
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
			
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
			BulletMesh->SetStaticMesh(gm->ObjectPooler->MonsterBulletMesh);
			BulletMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
			BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		}
		if (OwnerActor->ActorHasTag("Player"))
		{
			const AMainPawn* Player = Cast<AMainPawn>(OwnerActor);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
			BulletDamage=Player->GetBulletPower();
			ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
			BulletMesh->SetStaticMesh(gm->ObjectPooler->PlayeruBulletMesh);
			BulletMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
			BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
		}
	}
	
}



void ABullet::Deactivate()
{
	SetActive(false);
}

bool ABullet::IsActive()
{
	return Active;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

//	
}
void ABullet::SetVelocity(FVector Velocity)
{
	BulletMovement->Velocity = Velocity;
}
void ABullet::MoveToTarget(bool InActive)
{
	if(InActive)
	{
		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
		FVector Dir = player->GetActorLocation() - this->GetActorLocation();
		Dir.Normalize();// 방향벡터
		const FVector Movement = Dir * 300.f  ;// 
		FRotator NewRotation = Movement.Rotation();
		BulletMovement->Velocity = Movement;
		//RootComponent->MoveComponent(Movement, NewRotation, true);
		//BulletMovement->SetVelocityInLocalSpace(Movement);
		
	}

	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if(IsActive())
	// {
	// 	MoveToTarget();
	// }

//
}

