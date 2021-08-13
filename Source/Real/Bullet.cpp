// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"




// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//PrimaryActorTick.bCanEverTick = true;
		// 틱X
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Game/Mesh/BulletMesh.BulletMesh"));

	// Create mesh component for the projectile sphere
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	BulletMesh->SetStaticMesh(BulletMeshAsset.Object);
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetGenerateOverlapEvents(false);
	BulletMesh->BodyInstance.SetCollisionProfileName("Projectile");
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);		// set up a notification for when this component hits something
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
		//OtherActor->
		
	}

	// 몬스터 처리 
	if (OtherActor->ActorHasTag("Monster"))
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
	SetActorEnableCollision(InActive);
	SetActorHiddenInGame(!InActive);
	BulletMesh->SetActive(InActive);
	

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
//void ABullet::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void ABullet::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

