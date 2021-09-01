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



	// 모든 스킬 적용하기
	

	
	// 스킬 적용은 스킬 컴포넌트들 각자 만들어거 추가하는 방식으로 생성
	//Tarray<Object> RateUp;

	// ObJect는 스킬 오브젝트로해서 하나하나 제작 (버프, 디버프 , AoE, ) 

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
	void AddSkill(FName mSkillName);

	UFUNCTION(BlueprintCallable)
	void SkillLevelUp(FName mSkillName);
	

	void IceBulletCircle();

	
	
	void SetPlayerBuff( FPlayerSkillRow* mSkillRow , int mSkillLevel=0);
	void SetPlayerActiveSkill(FPlayerSkillRow* mSkillRow, int mSkillLevel=0);

};
