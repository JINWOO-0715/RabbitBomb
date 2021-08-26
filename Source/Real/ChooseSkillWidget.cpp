// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseSkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RealGameModeBase.h"
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
	SetRandomSkill();
	
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	 RemoveFromParent();

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
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	//여기에 랜덤을 넣어야겠지
	

	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowData(1);
	SkillOneText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
	
	PlayerSkillRowData = gm->GetPlayerSkillRowData(2);
	SkillTwoText->SetText(FText::FromName(PlayerSkillRowData->SKillName));

	PlayerSkillRowData = gm->GetPlayerSkillRowData(3);
	SkillTrdText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
	
}
