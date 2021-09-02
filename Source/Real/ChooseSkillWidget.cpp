// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseSkillWidget.h"

#include <list>
#include <string>

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



	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	PlayerPawn->SkillComp->AddSkill(0); //추가

	//PlayerPawn->SkillComp->HasSkill.Add(PlayerSkillRowData.SKillName,*PlayerSkillRowData.SkillActive);
	//
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->PlayerSkillChooseWidget->RemoveFromViewport();

	//
}

void UChooseSkillWidget::ChooseSkillTwo()
{
	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// 스킬 컴포넌트에 스킬을 추가해서 추가한 스킬은 알아서 작동되게

	PlayerPawn->SkillComp->AddSkill(SkillName[1]); //추가

	//PlayerPawn->SkillComp->HasSkill.Add(PlayerSkillRowData.SKillName,*PlayerSkillRowData.SkillActive);
	//
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->PlayerSkillChooseWidget->RemoveFromViewport();
	//	RemoveFromParent();
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));
}

void UChooseSkillWidget::ChooseSkillTrd()
{
	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// 스킬 컴포넌트에 스킬을 추가해서 추가한 스킬은 알아서 작동되게

	PlayerPawn->SkillComp->AddSkill(SkillName[2]); //추가

	//PlayerPawn->SkillComp->HasSkill.Add(PlayerSkillRowData.SKillName,*PlayerSkillRowData.SkillActive);
	//
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->PlayerSkillChooseWidget->RemoveFromViewport();
	//RemoveFromParent();
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));
}

void UChooseSkillWidget::SetRandomSkill()
{
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();


	// skillname[0,1,2]를 랜덤하게 설정만해주면됌 (중복없이)

	//
	// for(int i = 0 ; i<3;i++)
	// {
	// 	int rand = FMath::RandRange(0,3);
	// 	int rand2 = FMath::RandRange(0,3);
	// 	
	// 	int temp = SkillName[rand];
	// 	SkillName[rand] = SkillName[rand2];
	// 	SkillName[rand2]=temp;
	// }

	for(int i = 0 ; i<4;i++)
	{
		SkillName[i] = i;
	}

	for(int i = 0 ; i<3;i++)
	{
		int rand = FMath::RandRange(0,3);
		int rand2 = FMath::RandRange(0,3);
		
		int temp = SkillName[rand];
		SkillName[rand] = SkillName[rand2];
		SkillName[rand2]=temp;
	}

	
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(SkillName[0]));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(SkillName[1]));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(SkillName[2]));


	FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(SkillName[0]);
	
	if(PlayerSkillRowData)
	{
		
		SkillOneText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
	
	
		PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(SkillName[1]);
		SkillTwoText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
	
	
		PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(SkillName[2]);
		SkillTrdText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
	}
	
	//
}
