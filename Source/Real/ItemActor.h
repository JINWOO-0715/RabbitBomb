// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ItemActor.generated.h"

UCLASS()
class REAL_API AItemActor : public AActor
{
	GENERATED_BODY()
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemMesh;


	//올려주는 경험치
	float UPExp = 101.0f;

	
public:	
	// Sets default values for this actor's properties
	AItemActor();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//void SetUpExp();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE	float GetItemExp() const {return UPExp;};

	bool isFollowing ;
	void FollowingPlayer();
	

};
