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

	protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	
};
