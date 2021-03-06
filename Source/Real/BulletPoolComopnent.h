// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletPoolComopnent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UBulletPoolComopnent : public UActorComponent
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this component's properties
	UBulletPoolComopnent();

	// 들어간거 가져오는거
	class ABullet* GetPooledBullet();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void Spawn();

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	TSubclassOf<class ABullet> PooledBulletSubClass;
	
	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	int Poolsize = 100;

	UPROPERTY(EditAnywhere,Category	="ObjectPooler");
	class UStaticMesh* MonsterBulletMesh;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler");
	class UStaticMesh* PlayeruBulletMesh;

	TArray<ABullet*> Pool;
	
};
