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



protected:

	
public:
	ARealGameModeBase();
	virtual void BeginPlay() override;

	
	
	virtual void Tick(float DeltaTime) override;
	


	// 몬스터 담기 
	UPROPERTY(EditAnywhere,Category="Spawner")
		class UObjectPoolComponent* ObjectPooler;


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



	// Score위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UScoreWidget* PlayerScoreWidget;
};
	


