// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTableList.h"
#include "Components/ActorComponent.h"
#include "StageManageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REAL_API UStageManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStageManageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 데이터 테이블 Row get
	FGameStageRow* GetGameStateRowData(int rowN) const;
	FCommonMonsterData* GetCommonMonsterRowData(int rowN) const;
	//FWaveType* GetWaveType(int rowN) const;

	// 스테이지 시작 함수
	UFUNCTION(BlueprintCallable)
	void StageStart(int StageNum);

	UFUNCTION(BlueprintCallable)
	void IsClearWave();
	
	UFUNCTION(BlueprintCallable)
	void ClearWave();
	
	UPROPERTY(BlueprintReadWrite)
	int NowWave;

	UPROPERTY(BlueprintReadWrite)
	FWaveType NowWaveMonsterType;
	
	//데이터 테이블 
	UPROPERTY(BlueprintReadWrite)
	class UDataTable* GameStageData;

	UPROPERTY(BlueprintReadWrite)
	class UDataTable* CommonMonsterData;

	
};
