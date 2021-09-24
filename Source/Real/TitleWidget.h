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
	// ��������
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGametButton;

	//���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ShopText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ShopTextButton;


	// �������� ���� ��ư 5��
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


	// ���� ���� �ڽ�
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* EnterVerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EnterMapNameText;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackMapButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* EnterStageButton;

	// ���� �ڽ� ���̱� �Ⱥ��̱�
	UPROPERTY()
	bool isShowEnterBox;

	// ���� ��������?
	UPROPERTY()
	int NowPage = -1;

	// ���� �� ����������
	int Stage[5];

	// �� ��������
	int ChooseStage = 1;

	// ������ �� ��������
	int EndStage =10;
	


public:
	// ��ư ����
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
