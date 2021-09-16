// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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
	class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton;
public:
	UFUNCTION()
	void ShowButton();

	UFUNCTION()
	void GotoTitle();
	
	int count =0;
};
