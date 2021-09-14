// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MainPawn.h"

#include "ShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()


	virtual void NativeConstruct() override;
	protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HPUptext;

	UPROPERTY(meta = (BindWidget))
	class UButton* HpUpButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PowerUpText;

	UPROPERTY(meta = (BindWidget))
	class UButton* PowerUpButton;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SpeedUpText;

	UPROPERTY(meta = (BindWidget))
	class UButton* SpeedUpButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FireRateUpText;

	UPROPERTY(meta = (BindWidget))
	class UButton* FireRateUpButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BackText;

	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RemainCoinText;

	public:

	
	UFUNCTION(BlueprintCallable)
		void HpUpFun();

	UFUNCTION(BlueprintCallable)
	void PowerUpFun();
	UFUNCTION(BlueprintCallable)
	void SpeedUpFun();
	UFUNCTION(BlueprintCallable)
	void FireRateUpFun();


};
