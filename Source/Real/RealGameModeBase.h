// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "BulletPoolComopnent.h"
#include "ObjectPoolComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "PlayerSkillDataTable.h"
#include "ItemPoolComponent.h"
#include "GameStateDataTable.h"
#include "DataTableList.h"

#include "StageManageComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ChooseSkillWidget.h"


#include "RealGameModeBase.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ARealGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	//타이머 핸들
	UPROPERTY()
	FTimerHandle MonsterSpawnTimer;
	
	UPROPERTY()
	FWaveType NowMosterCount; 

protected:

	
public:
	ARealGameModeBase();
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere)
	class UDataTable*  CommonMonsterDataTable;

	// 스마트포인터 사용???
	UPROPERTY(BlueprintReadOnly)
	FDataTableManage DataTableManager;
	
	
	virtual void Tick(float DeltaTime) override;
	

	//총알 담기
	UPROPERTY(EditAnywhere,Category="Spawner")
		class 	UBulletPoolComopnent* BulletPooler;

	// 몬스터 담기 
	UPROPERTY(EditAnywhere,Category="Spawner")
		class UObjectPoolComponent* MonsterPooler;

	UPROPERTY(EditAnywhere,Category="Spawner")
		class UItemPoolComponent* ItemPooler;

	UPROPERTY(EditAnywhere,Category="Spawner")
		class UStageManageComponent* StageManageComponent;



	//클릭효과음
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* ClickSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* StatUpSound;

	//몬스터 죽는 효과음
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* MonsterDeadSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* MonsterHitSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* GameClearSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* LoseSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* LoseSound2;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* HitedParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* DeadParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* DeadParticle2;

	// // 플레이어 오른쪽아래 위젯
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UUserWidget> PlayerRightWidgetClass;
	//
	// // 플레이어 오른쪽아래 위젯
	// UPROPERTY(VisibleInstanceOnly)
	// class URightWidget* PlayerRightWidget;

	// 플레이어 스킬선택
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerSkillChooseClass;

	// 플레이어 스킬선택 위젯
	UPROPERTY(VisibleInstanceOnly)
	class UChooseSkillWidget* PlayerSkillChooseWidget;
	
	//게임저장
	UFUNCTION(BlueprintCallable)
	void Save();

	//게임 불러오기
	UFUNCTION(BlueprintCallable)
	void Load();


};
	


