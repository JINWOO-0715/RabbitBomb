// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include <ThirdParty/CryptoPP/5.6.5/include/misc.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerSkillDataTable.h"
#include "Components/Button.h"
#include "Kismet/KismetArrayLibrary.h"
#include "ChooseSkillWidget.generated.h"

/**
 * 
 */

UCLASS()
class REAL_API UChooseSkillWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SkillOneButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillOneText;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SkillTwoButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillTwoText;


	UPROPERTY(meta = (BindWidget))
	class UButton* SkillTrdButton;
	

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillTrdText;


public:


	
	UFUNCTION(BlueprintCallable)
	void ChooseSkillOne();
	
	UFUNCTION(BlueprintCallable)
	void ChooseSkillTwo();

	UFUNCTION(BlueprintCallable)
	void ChooseSkillTrd();
	
	// UFUNCTION()
	// void SetRandomSkill();

	const int skillSize =4;
	
	UPROPERTY()
	int SkillName[4];
	
	UPROPERTY()
	int32 SkillSize=4;

	
	UPROPERTY()
	FName SkillFName[4];

	TArray<int> skillInt;
	// UPROPERTY()
	// FPlayerSkillRow PlayerSkillRowData;

	// UPROPERTY()
	// FPlayerSkillRow PlayerSkillRowData;
	//
	// UPROPERTY()
	// FPlayerSkillRow PlayerSkillRowData;
};
