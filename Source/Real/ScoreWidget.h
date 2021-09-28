// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RabbitBombGameInstance.h"
#include "Components/VerticalBox.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;

	protected:

	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NowWaveText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RemainMonsterTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnGameButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* StageClearbox;
	
public:
	UFUNCTION()
	void ShowButton();

	UFUNCTION()
	void GotoTitle();
	
	UFUNCTION()
	void SetRemainMonsterText(int remainMonsterNum);

	UFUNCTION()
	void DereaseMonsterText();
	
	UFUNCTION()
	void SetNowWaveText(int mNowWave , int mGoal);

	UFUNCTION()
	void ShowStageClearBox(bool isShow);
	
	int count =0;
	int remainNum=1;
	
	//클릭효과음
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* ClickSound;
	
};
