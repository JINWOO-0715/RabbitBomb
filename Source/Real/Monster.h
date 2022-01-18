// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletAttackPattern.h"
#include "MonsterDataTable.h"
#include "DataTableList.h"

#include "Monster.generated.h"


UCLASS(Abstract)
class REAL_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonster();
	
	virtual void Mfire() PURE_VIRTUAL(AMonster);

	bool Active;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	//virtual void DeActive();
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// 공격 패턴 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackStyle")
	class UBulletAttackPattern* AttackPatternComponent;

	//메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* MonsterMeshComponent;

	// Stat구조체
	FMonsterRow MonsterStat;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Stat" )
	float MonsterHP;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 몬스터 초기화
	virtual void InitMonster(const FCommonMonsterData* MonsterType);
	// 
	bool bCanFire;

	UFUNCTION(BlueprintCallable)
	void SetActive(bool InActive);
	
	UFUNCTION(BlueprintCallable)
	virtual bool IsActive(); 
	 
	UFUNCTION(BlueprintCallable)
	virtual void ShotTimerExpired();
	
	// 타이머 핸들
	UPROPERTY(EditAnywhere)
	FTimerHandle AttackTimer;


};


