// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterDataTable.h"
#include "PaperSpriteComponent.h"
#include "BulletAttackPattern.h"
#include "PaperFlipbook.h"

#include "PaperSprite.h"
#include "MonsterActor.generated.h"

UCLASS()
class REAL_API AMonsterActor : public AActor
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprites")
		class UBulletAttackPattern* AttackPatternComponent;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MonsterMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprites")
	class UPaperSpriteComponent* Imoge;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MonsterHP = 50.f;


	UFUNCTION()
	void MoveToTarget();

	// float LifeSpan = 5.0f;

	//5�ʵ��� ��Ƴ���
	float Lifespan = 5.0f;

	// ����
	float FireRate = 1.0f;
	
	// �Ѿ� �ӵ�
	float BulletSpeed = 500.0f;
	
	// Ÿ�̸� �ڵ� �̸�
	FTimerHandle LifespanTimer;
	FTimerHandle AttackTimer;
	FTimerHandle StunTimer;
	FTimerHandle MTChangeTimer;
	
//	FTimerHandle MovespanTimer;
	
	UPROPERTY(EditAnywhere,Category="Spawner")
	float BulletLifeSpan = 5.0f;
	float HPPowerfulNum = 0.001f;


	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	
	bool Active;
	bool bCanFire;
	bool isStun;
	void Deactivate();
	void StunMonster();
	void ChangeHitedMTTimer();
	void ChangeHitMT();


	
public:	
	// Sets default values for this actor's properties
	AMonsterActor();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed =100.0f;
	
	//UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	//float MovetoTagetUpdateDuration =0.1f;
	
	virtual void SetLifeSpan(float InLifespan) override;
	
	UFUNCTION(BlueprintCallable)
	void SetActive(bool InActive);

	UPROPERTY(EditAnywhere,Category	="MonsterMesh");
	class UMaterialInterface* MonsterHitedMT;
	
	void ShotTimerExpired();
	virtual void FireShot();
	void InitMonster(int dataRowN);
	
	bool IsActive();
	//// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	//
	// �Ѿ� �Ŀ�
	float BulletPower = 10.0f;

	void SetStunMonster(float mStunTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
