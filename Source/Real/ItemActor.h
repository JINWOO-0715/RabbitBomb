// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "MainPawn.h"

#include "ItemActor.generated.h"

UCLASS()
class REAL_API AItemActor : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AItemActor();
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//void SetUpExp();
	//
	// 발사 사운드
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* GetItemSound;

protected:
	// Called when the game starts or when spawned
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemMesh;


	//올려주는 경험치
	float UPExp = 10100.0f;
	bool Active;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE	float GetItemExp() const {return UPExp;};

	bool isFollowing;

	void FollowingPlayer();
	bool IsActive();
	void SetActive(bool InActive);

};
