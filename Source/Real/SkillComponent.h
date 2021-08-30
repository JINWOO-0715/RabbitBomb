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



	// string/int ������ ���̳� ��ų��ȣ/int������ ������ ��ų ��������
	int SkillLevel;

	FName SkillName;

	// ��� ��ų �����ϱ�
	

	
	// ��ų ������ ��ų ������Ʈ�� ���� ������ �߰��ϴ� ������� ����
	//Tarray<Object> RateUp;

	// ObJect�� ��ų ������Ʈ���ؼ� �ϳ��ϳ� ���� (����, ����� , AoE, ) 

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
