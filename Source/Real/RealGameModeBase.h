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

	//Ÿ�̸� �ڵ�
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

	// ����Ʈ������ ���???
	UPROPERTY(BlueprintReadOnly)
	FDataTableManage DataTableManager;
	
	
	virtual void Tick(float DeltaTime) override;
	

	//�Ѿ� ���
	UPROPERTY(EditAnywhere,Category="Spawner")
		class 	UBulletPoolComopnent* BulletPooler;

	// ���� ��� 
	UPROPERTY(EditAnywhere,Category="Spawner")
		class UObjectPoolComponent* MonsterPooler;

	UPROPERTY(EditAnywhere,Category="Spawner")
		class UItemPoolComponent* ItemPooler;

	UPROPERTY(EditAnywhere,Category="Spawner")
		class UStageManageComponent* StageManageComponent;



	//Ŭ��ȿ����
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* ClickSound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* StatUpSound;

	//���� �״� ȿ����
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

	// // �÷��̾� �����ʾƷ� ����
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UUserWidget> PlayerRightWidgetClass;
	//
	// // �÷��̾� �����ʾƷ� ����
	// UPROPERTY(VisibleInstanceOnly)
	// class URightWidget* PlayerRightWidget;

	// �÷��̾� ��ų����
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerSkillChooseClass;

	// �÷��̾� ��ų���� ����
	UPROPERTY(VisibleInstanceOnly)
	class UChooseSkillWidget* PlayerSkillChooseWidget;
	
	//��������
	UFUNCTION(BlueprintCallable)
	void Save();

	//���� �ҷ�����
	UFUNCTION(BlueprintCallable)
	void Load();


};
	


