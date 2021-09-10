// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


#include "MainInGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API UMainInGameWidget : public UUserWidget
{
	GENERATED_BODY()


	protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MapHP;
	
	public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;

	
	// public:
	// UFUNCTION()
	// void SetHpPersent();
};