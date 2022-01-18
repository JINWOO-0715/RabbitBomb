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

	// ���� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackStyle")
	class UBulletAttackPattern* AttackPatternComponent;

	//�޽� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* MonsterMeshComponent;

	// Stat����ü
	FMonsterRow MonsterStat;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Stat" )
	float MonsterHP;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���� �ʱ�ȭ
	virtual void InitMonster(const FCommonMonsterData* MonsterType);
	// 
	bool bCanFire;

	UFUNCTION(BlueprintCallable)
	void SetActive(bool InActive);
	
	UFUNCTION(BlueprintCallable)
	virtual bool IsActive(); 
	 
	UFUNCTION(BlueprintCallable)
	virtual void ShotTimerExpired();
	
	// Ÿ�̸� �ڵ�
	UPROPERTY(EditAnywhere)
	FTimerHandle AttackTimer;


};


