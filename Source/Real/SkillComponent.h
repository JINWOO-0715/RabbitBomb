// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSkillDataTable.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

	

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillSet")
	TMap<FName,int> HasSkill;

	UPROPERTY(EditAnywhere,Category="SkillSet")
	TArray<UObject*> HasSkillObjects;

	UPROPERTY(EditAnywhere,Category="SkillSet")
	AActor* OwnerActor ;
	
	void ActiveSkill(FPlayerSkillRow* mSkillRow ,FName mSkillName);
	
	UFUNCTION(BlueprintCallable)
	void AddSkill(int mSkillInt);
	
	UFUNCTION(BlueprintCallable)
	void SkillLevelUp(FName mSkillName);
	
	UFUNCTION(BlueprintCallable)
	void IceBulletCircle();


	void SetPlayerBuff( FPlayerSkillRow* mSkillRow , int mSkillLevel=0);
	
	
	void SetPlayerActiveSkill(FPlayerSkillRow* mSkillRow, int mSkillLevel=0);

};
