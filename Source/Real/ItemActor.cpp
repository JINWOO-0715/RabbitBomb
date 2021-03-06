// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Game/Mesh/ExpMesh.ExpMesh"));

	// Create mesh component for the projectile sphere
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent=ItemMesh;

	ItemMesh->SetStaticMesh(BulletMeshAsset.Object);
	ItemMesh->SetGenerateOverlapEvents(false);
	ItemMesh->OnComponentHit.AddDynamic(this, &AItemActor::OnHit);
	ItemMesh->SetNotifyRigidBodyCollision(true);
	Tags.Add("Item");
	static ConstructorHelpers::FObjectFinder<USoundBase> GettingAudio(TEXT("/Game/Sound/get_item_.get_item_"));
	GetItemSound =GettingAudio.Object;
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 니가 오게 하는 함수를 작동한다.
	FollowingPlayer();

}

void AItemActor::FollowingPlayer()
{
	if(isFollowing)
	{
		AActor* player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
		FVector Dir = player->GetActorLocation() - GetActorLocation();
		Dir.Normalize();// 방향벡터
		const FVector Movement = Dir * 10.f  ;//
		FRotator NewRotation = Movement.Rotation();
		RootComponent->MoveComponent(Movement,NewRotation,true);

	}
}

bool AItemActor::IsActive()
{
	return Active;
}

void AItemActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::PlaySoundAtLocation(this, GetItemSound, GetActorLocation());
		isFollowing=false;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("COllision BoxItem"));
		AMainPawn* Player = Cast<AMainPawn>(OtherActor);
		Player->GetExperience(UPExp);
		//Player.add
		Destroy();
	}
	
}

void AItemActor::SetActive(bool InActive)
{
	Active =InActive;
	ItemMesh->SetGenerateOverlapEvents(InActive);
	ItemMesh->SetNotifyRigidBodyCollision(InActive);
	// 충돌off
	SetActorEnableCollision(InActive);
	// 숨기기
	SetActorHiddenInGame(!InActive);
	// 메시지우기
	ItemMesh->SetActive(InActive);
	// 틱종료
	SetActorTickEnabled(InActive);

}
