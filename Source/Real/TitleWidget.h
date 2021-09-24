// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "RealGameModeBase.h"

#include "Components/Button.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	//virtual void NativeConstruct() override;

	virtual void NativeConstruct() override;

protected:
	// 게임종료
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGametButton;

	//상점 텍스트
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ShopText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ShopTextButton;


	// 스테이지 입장 버튼 5개
	UPROPERTY(meta = (BindWidget))
	class UButton* StageOneEnterButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StageOneEnterText;


	UPROPERTY(meta = (BindWidget))
	class UButton* StageTwoEnterButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StageTwoEnterText;

	UPROPERTY(meta = (BindWidget))
	class UButton* StageTirEnterButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StageTirEnterText;


	UPROPERTY(meta = (BindWidget))
	class UButton* StageOFourEnterButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StageFourEnterText;

	UPROPERTY(meta = (BindWidget))
	class UButton* StageFiveEnterButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StageFiveEnterText;


	UPROPERTY(meta = (BindWidget))
	class UButton* NextPageButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* BeforePageButton;


	// 입장 관련 박스
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* EnterVerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EnterMapNameText;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackMapButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* EnterStageButton;

	// 들어는 박스 보이기 안보이기
	UPROPERTY()
	bool isShowEnterBox;

	// 지금 몇페이지?
	UPROPERTY()
	int NowPage = -1;

	// 지금 깔린 스테이지들
	int Stage[5];

	// 고른 스테이지
	int ChooseStage = 1;

	// 구현한 끝 스테이지
	int EndStage =10;
	


public:
	// 버튼 반응
	UFUNCTION(BlueprintCallable)
	void ClickStageOneButton();
	UFUNCTION(BlueprintCallable)
	void ClickStageTwoButton();
	UFUNCTION(BlueprintCallable)
	void ClickStageTirButton();
	UFUNCTION(BlueprintCallable)
	void ClickStageFourButton();
	UFUNCTION(BlueprintCallable)
	void ClickStageFiveButton();


	UFUNCTION(BlueprintCallable)
	void Quitgame();
	UFUNCTION(BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintCallable)
	void ShowEnterBox();

	UFUNCTION(BlueprintCallable)
	void IncreasePage();

	UFUNCTION(BlueprintCallable)
	void DecreasePage();
};
