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



	// string/int 형식의 맵이나 스킬번호/int형식의 맵으로 스킬 레벨관리
	int SkillLevel;

	FName SkillName;

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

	UPROPERTY(EditAnywhere,Category="SkillSet")
	TMap<FName,int> HasSkill;

	UPROPERTY(EditAnywhere,Category="SkillSet")
	TArray<UObject*> HasSkillObjects;
	
	UFUNCTION(BlueprintCallable)
	void ActiveSkill();

	UFUNCTION(BlueprintCallable)
	void AddSkill(FName mSkillName);

	UFUNCTION(BlueprintCallable)
	void SkillLevelUp(FName mSkillName);

	void SetPlayerBuff(FPlayerSkillRow* mSkillRow);
	

};
