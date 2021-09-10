// Fill out your copyright notice in the Description page of Project Settings.


#include "HPItemActor.h"
#include "MainPawn.h"

AHPItemActor::AHPItemActor()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/HpMesh.HpMesh"));
	ItemMesh->SetStaticMesh(MeshAsset.Object);

	UPExp =20.f;

}

void AHPItemActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		isFollowing=false;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("COllision BoxItem"));
		AMainPawn* Player = Cast<AMainPawn>(OtherActor);
		Player->UpHp(UPExp);
		//Player.add
		Destroy();
	}
}
