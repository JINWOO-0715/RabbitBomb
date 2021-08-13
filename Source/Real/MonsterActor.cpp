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
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/MonsterMesh.MonsterMesh"));
	MonseterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MonseterMeshComponent;
	SetActorEnableCollision(false);
	//MonseterMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MonseterMeshComponent->SetStaticMesh(MeshAsset.Object);

	MonseterMeshComponent->SetGenerateOverlapEvents(false);
    Tags.Add("Monster");


    //OnTakeAnyDamage.AddDynamic(this, &AMonsterActor::TakeDamage);
}

// 생명 주기 외부에서 설정가능하게 제작
void AMonsterActor::SetLifeSpan(float InLifespan)
{
	Lifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer,this
		,&AMonsterActor::Deactivate,Lifespan,false);
	

}

// 활성화시  
void AMonsterActor::SetActive(bool InActive)
{
	
		Active =InActive;
		SetActorEnableCollision(InActive);
		SetActorHiddenInGame(!InActive);
		MonseterMeshComponent->SetActive(InActive);

		// 여기에 새로운 타이머를 넣는다?  0.3변수로 쓰세요
		GetWorldTimerManager().SetTimer(MovespanTimer,this
			,&AMonsterActor::MoveToTarget,MovetoTagetUpdateDuration,InActive);
}

// 테스트 꼭 고치거나 지울것. -> 이걸 최적화 할 방법은 없는건가!? 
void AMonsterActor::MoveToTarget()
{
	AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	FVector Dir = player->GetActorLocation() - this->GetActorLocation();
	Dir.Normalize();
	const FVector Movement = Dir * MoveSpeed * MovetoTagetUpdateDuration;
	FRotator NewRotation = Movement.Rotation();
	RootComponent->MoveComponent(Movement, NewRotation, true);

	
}

bool AMonsterActor::IsActive()
{
	return Active;
}
void AMonsterActor::Deactivate()
{
	// 여기에 타이머 종료를 넣는다. 
	SetActive(false);
	MonseterMeshComponent->Deactivate();
	
}


// 오버라이드 사용
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
//void AMonsterActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

