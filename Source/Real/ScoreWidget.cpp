// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExitGameButton->OnPressed.AddDynamic(this, &UScoreWidget::GotoTitle);
	ReturnGameButton->OnPressed.AddDynamic(this, &UScoreWidget::ShowButton);
	ExitGameButton->SetVisibility(ESlateVisibility::Hidden);
	ReturnGameButton->SetVisibility(ESlateVisibility::Hidden);
}

void UScoreWidget::ShowButton()
{
	count++;
	if(count%2==1)
	{
		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		if (MyPlayer != NULL)
		{
			MyPlayer->SetPause(true);
		}
		ExitGameButton->SetVisibility(ESlateVisibility::Visible);
		ReturnGameButton->SetVisibility(ESlateVisibility::Visible);
		
	}
	else
	{
		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		if (MyPlayer != NULL)
		{
			MyPlayer->SetPause(false);
		}
		ExitGameButton->SetVisibility(ESlateVisibility::Hidden);
		ReturnGameButton->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UScoreWidget::GotoTitle()
{
	UGameplayStatics::OpenLevel(this, FName("TitleLevel"), true);
}
