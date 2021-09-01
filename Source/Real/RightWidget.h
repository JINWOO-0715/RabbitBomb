// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include <ThirdParty/CryptoPP/5.6.5/include/misc.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "RightWidget.generated.h"

/**
 * 
 */
UCLASS()
class REAL_API URightWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FireText;

	UPROPERTY(meta = (BindWidget))
	class UButton* FireButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DashText;

	UPROPERTY(meta = (BindWidget))
	class UButton* DashButton;

	// ÃÑ¾Ë On OFf
	UFUNCTION()
	void FireOn();
	
	UFUNCTION()
	void FireOff();

	UFUNCTION()
	void DashOn();
	
public:
	UPROPERTY()
	class AMainPawn* Player;
	
	UPROPERTY()
	FTimerHandle TimerHandle_ShotTimerExpired;
	
	UFUNCTION()
	void SetPlayer();
};
