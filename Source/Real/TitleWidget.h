// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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


	protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameStartText;

	UPROPERTY(meta = (BindWidget))
	class UButton* GameStartTextButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ShopText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ShopTextButton;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OptionText;

	UPROPERTY(meta = (BindWidget))
	class UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MapNameText;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackMapNameButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* FowardMapNameButton;
	public:
	
};
