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
	// ���� �����ͼ� ��ų������Ʈ�� ��ų �߰� ��ų�߰��� playerPawn���� �Լ��� �˾Ƽ� �۵��ǰ�.

   //PlayerSkillRowData.SkillActive

	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// ��ų ������Ʈ�� ��ų�� �߰��ؼ� �߰��� ��ų�� �˾Ƽ� �۵��ǰ�

	PlayerPawn->SkillComp->AddSkill(FName("IceBullet"));//�߰�
	
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

	//���⿡ ������ �־�߰���
	
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
