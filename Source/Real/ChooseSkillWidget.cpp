// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseSkillWidget.h"

#include <ThirdParty/PhysX3/PxShared/src/foundation/include/PsArray.h>

#include "Kismet/GameplayStatics.h"
#include "RealGameModeBase.h"
#include "MainPawn.h"
#include "components/Button.h"


void UChooseSkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SkillOneButton->SetVisibility(ESlateVisibility::Hidden);
	SkillTwoButton->SetVisibility(ESlateVisibility::Hidden);
	SkillTrdButton->SetVisibility(ESlateVisibility::Hidden);
	//DashButton->OnReleased.AddDynamic(this, &URightWidget::FireOff);
}


void UChooseSkillWidget::ChooseSkillOne()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed"));


	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//PlayerPawn->SkillComp->AddSkill(skillInt[0]); //�߰�

	//PlayerPawn->SkillComp->HasSkill.Add(PlayerSkillRowData.SKillName,*PlayerSkillRowData.SkillActive);
	//
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(false);
	}
	skillInt.Reset();
	gm->PlayerSkillChooseWidget->RemoveFromViewport();

	//
}

void UChooseSkillWidget::ChooseSkillTwo()
{
	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// ��ų ������Ʈ�� ��ų�� �߰��ؼ� �߰��� ��ų�� �˾Ƽ� �۵��ǰ�

	PlayerPawn->SkillComp->AddSkill(skillInt[1]); //�߰�

	//PlayerPawn->SkillComp->HasSkill.Add(PlayerSkillRowData.SKillName,*PlayerSkillRowData.SkillActive);
	//
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(false);
	}
	skillInt.Reset();
	gm->PlayerSkillChooseWidget->RemoveFromViewport();
	//	RemoveFromParent();
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));
}

void UChooseSkillWidget::ChooseSkillTrd()
{
	AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// ��ų ������Ʈ�� ��ų�� �߰��ؼ� �߰��� ��ų�� �˾Ƽ� �۵��ǰ�

	PlayerPawn->SkillComp->AddSkill(skillInt[2]); //�߰�

	//PlayerPawn->SkillComp->HasSkill.Add(PlayerSkillRowData.SKillName,*PlayerSkillRowData.SkillActive);
	//
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(false);
	}
	skillInt.Reset();
	gm->PlayerSkillChooseWidget->RemoveFromViewport();

	//RemoveFromParent();
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));
}
//
// void UChooseSkillWidget::SetRandomSkill()
// {
// 	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
// 	AMainPawn* player = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
//
// 	for (int i = 0; i < 4; i++)
// 	{
// 		SkillName[i] = i;
// 		SkillFName[i] = gm->GetPlayerSkillRowDataToNum(i)->SKillName;
// 	}
//
//
// 	for (int i = 0; i < 4; i++)
// 	{
// 		// �÷��̾ �ְ� �����Ͱ� �ƴϸ� �߰�
// 		if (player->SkillComp->HasSkill.Find(SkillFName[i]))
// 		{
// 			if (player->SkillComp->HasSkill[SkillFName[i]] < gm->GetPlayerSkillRowDataToNum(i)->MaxLevel)
// 			{
// 				// ������ �ȵȰ͸� �ִ´�.
// 				skillInt.Add(i);
// 			}
// 		} //���� ��ų�̸� �߰�
// 		else
// 		{
// 			skillInt.Add(i);
// 		}
// 	}
//
// 	//���´�.
// 	if (skillInt.Num() > 0)
// 	{
// 		
// 		int32 LastIndex = skillInt.Num() - 1;
// 		for (int32 i = 0; i <= LastIndex; ++i)
// 		{
// 			int32 Index = FMath::RandRange(i, LastIndex);
// 			if (i != Index)
// 			{
// 				skillInt.Swap(i, Index);
// 			}
// 		}
// 	}
//
//
// 	// for (int i = 0; i < 3; i++)
// 	// {
// 	// 	int rand = FMath::RandRange(0, 3);
// 	// 	int rand2 = FMath::RandRange(0, 3);
// 	// 	int temp = SkillName[rand];
// 	// 	SkillName[rand] = SkillName[rand2];
// 	// 	SkillName[rand2] = temp;
// 	// }
// 	//
// 	//
// 	// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(skillInt[0]));
// 	// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(skillInt[1]));
// 	// GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(skillInt[2]));
//
// 	// ��ų�� 2���ۿ� �ȳ������
//
// 	if (skillInt.Num()==2)
// 	{
// 		FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(skillInt[0]);
// 		if(PlayerSkillRowData)
// 		{
// 			
// 			SkillOneButton->SetVisibility(ESlateVisibility::Visible);
// 			SkillTwoButton->SetVisibility(ESlateVisibility::Visible);
// 			SkillOneText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 		 	PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(skillInt[1]);
// 		 	SkillTwoText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
//
// 		}
// 		
// 		// FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(SkillName[0]);
// 		//
// 		// if(PlayerSkillRowData)
// 		// {
// 		// 	
// 		// 	SkillOneText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 		//
// 		// 	PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(SkillName[1]);
// 		// 	SkillTwoText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 		//
// 		//
// 		// 	PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(SkillName[2]);
// 		// 	SkillTrdText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 		// }
// 	}	// 1���ۿ� �ȳ������ �׿�
// 	else if (skillInt.Num() == 1)
// 	{
// 		FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(skillInt[0]);
// 		if(PlayerSkillRowData)
// 		{
// 			
// 			SkillOneButton->SetVisibility(ESlateVisibility::Visible);
//
// 			SkillOneText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 		
// 		}
// 	}
// 	else
// 	{
// 		FPlayerSkillRow* PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(skillInt[0]);
// 		if(PlayerSkillRowData)
// 		{
// 			SkillOneButton->SetVisibility(ESlateVisibility::Visible);
// 			SkillTwoButton->SetVisibility(ESlateVisibility::Visible);
// 			SkillTrdButton->SetVisibility(ESlateVisibility::Visible);
// 			
// 			
//
// 			SkillOneText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 			
// 			PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(skillInt[1]);
// 			SkillTwoText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 			
// 			PlayerSkillRowData = gm->GetPlayerSkillRowDataToNum(skillInt[2]);
// 			SkillTrdText->SetText(FText::FromName(PlayerSkillRowData->SKillName));
// 		
// 		}
// 	}
// }
