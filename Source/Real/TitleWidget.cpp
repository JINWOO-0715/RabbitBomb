// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OptionButton->OnPressed.AddDynamic(this, &UTitleWidget::Quitgame);
	GameStartTextButton->OnPressed.AddDynamic(this, &UTitleWidget::GameStart);
}

void UTitleWidget::Quitgame()
{
	 UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController() , EQuitPreference::Quit, true);
	
}
void UTitleWidget::GameStart()
{
	UGameplayStatics::OpenLevel(this, FName("MainLevel"), true);
}
