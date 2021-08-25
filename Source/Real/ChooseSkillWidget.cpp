// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseSkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainPawn.h"
#include "components/Button.h"


void UChooseSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SkillOneButton->OnClicked.AddDynamic(this, &UChooseSkillWidget::ChooseSkillOne);
	SkillTwoButton->OnClicked.AddDynamic(this, &UChooseSkillWidget::ChooseSkillTwo);
	SkillTrdButton->OnClicked.AddDynamic(this, &UChooseSkillWidget::ChooseSkillTrd);
	//DashButton->OnReleased.AddDynamic(this, &URightWidget::FireOff);
}

void UChooseSkillWidget::ChooseSkillOne()
{
	 // ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	 // int a =1;
	 // auto c = gm->GetPlayerSkillRowData(a);
	 // SkillOneText->SetText(FText::FromName(c->SKillName));
	 //UE_LOG(LogTemp, Warning, TEXT("Pressed"));

}

void UChooseSkillWidget::ChooseSkillTwo()
{
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));

}

void UChooseSkillWidget::ChooseSkillTrd()
{
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));

}

void UChooseSkillWidget::SetRandomSkill()
{
}
