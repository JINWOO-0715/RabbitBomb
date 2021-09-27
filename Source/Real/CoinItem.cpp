// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"

ACoinItem::ACoinItem()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Mesh/coin.coin"));
	ItemMesh->SetStaticMesh(MeshAsset.Object);

	UPExp =200.f;
}

void ACoinItem::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		isFollowing=false;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("COllision BoxItem"));
		AMainPawn* Player = Cast<AMainPawn>(OtherActor);
		Player->UpPlayerCoin(UPExp);
		//Player.add
		Destroy();
	}
}
