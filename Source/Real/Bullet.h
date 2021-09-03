// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RealGameModeBase.h"
#include "MonsterActor.h"
#include "MainPawn.h"

#include "Bullet.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config = Game)
class REAL_API ABullet : public AActor
{
	GENERATED_BODY()
	
	//메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BulletMesh;



	//총알 움직임 컴포넌트 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* BulletMovement;



	// 타이머 핸들 이름
	FTimerHandle LifespanTimer;
	FTimerHandle MovespanTimer;
	FTimerHandle TimerHandle_ShotTimerExpired;

	//
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Active;

	float BulletDamage = 10.f;


	//5초간 총알 유지
	float Lifespan = 5.0f;
	//비활성화
	void Deactivate();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ABullet();
	

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float BulletMoveSpeed =300.f;
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MovetoTagetUpdateDuration =0.1f;
	
	virtual void SetLifeSpan(float InLifespan=5.0f) override;
	void SetActive(bool InActive);
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	AActor* OwnerActor;
	
	UFUNCTION(BlueprintCallable)
	void SetOwnerActor(AActor* ActorClass);

	
	void SetVelocity(FVector Velocity);
	
	bool IsActive();

	void MoveToTarget(bool InActive);

	FName BulletType;

	
	//메쉬 getter
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return BulletMesh; }
	// 총알 움직임 getter
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return BulletMovement; }

};
