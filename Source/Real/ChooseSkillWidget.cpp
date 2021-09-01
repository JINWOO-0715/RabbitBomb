// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseSkillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RealGameModeBase.h"
#include "MainPawn.h"
#include "components/Button.h"


void UChooseSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();


	//DashButton->OnReleased.AddDynamic(this, &URightWidget::FireOff);
}

void UChooseSkillWidget::ChooseSkillOne()
{

	UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	// 폰을 가져와서 스킬컴포넌트에 스킬 추가 스킬추가는 playerPawn에서 함수로 알아서 작동되게.

   //PlayerSkillRowData.SkillActive

	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// 스킬 컴포넌트에 스킬을 추가해서 추가한 스킬은 알아서 작동되게

	PlayerPawn->SkillComp->AddSkill(FName("IceBullet"));//추가
	
	//PlayerPawn->SkillComp->HasSkill.Add(PlayerSkillRowData.SKillName,*PlayerSkillRowData.SkillActive);
	//
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->PlayerSkillChooseWidget->RemoveFromViewport();

	//

}

void UChooseSkillWidget::ChooseSkillTwo()
{
	
//	RemoveFromParent();
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));

}

void UChooseSkillWidget::ChooseSkillTrd()
{
	//RemoveFromParent();
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));

}

void UChooseSkillWidget::SetRandomSkill()
{
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();

	//여기에 랜덤을 넣어야겠지
	
	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(FName("LaunchIncrease"));
	//FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowData(1);
	if(PlayerSkillRowData)
	{
		SkillOneText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
	
		PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(FName("Powerful"));
		SkillTwoText->SetText(FText::FromName(PlayerSkillRowData->SKillName));

		PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(FName("IceBullet"));
		SkillTrdText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
	}
	
	
}
