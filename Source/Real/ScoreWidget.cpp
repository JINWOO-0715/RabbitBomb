// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExitGameButton->OnPressed.AddDynamic(this, &UScoreWidget::GotoTitle);

	ExitGameButton->SetVisibility(ESlateVisibility::Hidden);

}

void UScoreWidget::ShowButton()
{
	count++;
	if(count%2==1)
	{
		ExitGameButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ExitGameButton->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UScoreWidget::GotoTitle()
{
	UGameplayStatics::OpenLevel(this, FName("TitleLevel"), true);
}
