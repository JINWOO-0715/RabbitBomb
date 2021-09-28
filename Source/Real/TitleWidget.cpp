// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"

#include "RabbitBombGameInstance.h"
#include "Components/VerticalBox.h"



void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuitGametButton->OnPressed.AddDynamic(this, &UTitleWidget::Quitgame);
	EnterStageButton->OnPressed.AddDynamic(this, &UTitleWidget::GameStart);
	
	BackMapButton->OnPressed.AddDynamic(this, &UTitleWidget::ShowEnterBox);
	NextPageButton->OnReleased.AddDynamic(this, &UTitleWidget::IncreasePage);
	BeforePageButton->OnReleased.AddDynamic(this, &UTitleWidget::DecreasePage);
	
	isShowEnterBox=false;

	
	StageOneEnterButton->OnReleased.AddDynamic(this, &UTitleWidget::ClickStageOneButton);
	StageTwoEnterButton->OnReleased.AddDynamic(this, &UTitleWidget::ClickStageTwoButton);
	StageTirEnterButton->OnReleased.AddDynamic(this, &UTitleWidget::ClickStageTirButton);
	StageOFourEnterButton->OnReleased.AddDynamic(this, &UTitleWidget::ClickStageFourButton);
	StageFiveEnterButton->OnReleased.AddDynamic(this, &UTitleWidget::ClickStageFiveButton);
	
	ShowEnterBox();
	IncreasePage();
}

void UTitleWidget::ClickStageOneButton()
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[0])));
	ChooseStage=Stage[0];
	ShowEnterBox();
}

void UTitleWidget::ClickStageTwoButton()
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[1])));
	ChooseStage=Stage[1];
	ShowEnterBox();
}

void UTitleWidget::ClickStageTirButton()
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[2])));
	ChooseStage=Stage[2];
	ShowEnterBox();		

}

void UTitleWidget::ClickStageFourButton()
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[3])));
	ChooseStage=Stage[3];
	ShowEnterBox();
}

void UTitleWidget::ClickStageFiveButton()
{	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[4])));
	ChooseStage=Stage[4];
	ShowEnterBox();
}

void UTitleWidget::Quitgame()
{
	
	 UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController() , EQuitPreference::Quit, true);
	
}
void UTitleWidget::GameStart()
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GameInstanceRef)
	{
		GameInstanceRef->NowStage =ChooseStage;
	}
	UGameplayStatics::OpenLevel(this, FName("MainLevel"), true);
}

void UTitleWidget::ShowEnterBox()
{
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	if(isShowEnterBox)
	{
		EnterVerticalBox->SetVisibility(ESlateVisibility::Visible);
		isShowEnterBox=!isShowEnterBox;
	}
	else
	{
		EnterVerticalBox->SetVisibility(ESlateVisibility::Hidden);
		isShowEnterBox=!isShowEnterBox;
	}
	
	
}

void UTitleWidget::IncreasePage()
{
	// ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	// int AddPage = gm->NowStage/5;
	// NowPage+=AddPage;
	// 22´Ü°è / 5 4
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	NowPage++;
	for(int i = 0 ; i <5;i++)
	{
		Stage[i] = (i+1)+(NowPage*5);
		
	}
	StageOneEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[0])));
	StageTwoEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[1])));
	StageTirEnterText->SetText(FText::FromString(FString::Printf(TEXT("Stage %d"), Stage[2])));
	StageFourEnterText->SetText(FText::FromString(FString::Printf(TEXT("Stage %d"), Stage[3])));
	StageFiveEnterText->SetText(FText::FromString(FString::Printf(TEXT("Stage %d"), Stage[4])));


	if (Stage[0] > EndStage)
	{
		StageOneEnterButton->SetIsEnabled(false);
	}
	else
	{
		StageOneEnterButton->SetIsEnabled(true);
	}
	if (Stage[1] > EndStage)
	{
		StageTwoEnterButton->SetIsEnabled(false);
	}else
	{
		StageTwoEnterButton->SetIsEnabled(true);
	}
	if (Stage[2] > EndStage)
	{
		StageTirEnterButton->SetIsEnabled(false);
	}else
	{
		StageTirEnterButton->SetIsEnabled(true);
	}
	if (Stage[3] > EndStage)
	{
		StageOFourEnterButton->SetIsEnabled(false);
	}else
	{
		StageOFourEnterButton->SetIsEnabled(true);
	}
	if (Stage[4] > EndStage)
	{
		StageFiveEnterButton->SetIsEnabled(false);
	}else
	{
		StageFiveEnterButton->SetIsEnabled(true);
	}
	
	
}

void UTitleWidget::DecreasePage()
{	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::PlaySound2D(this, gm->ClickSound);
	if(NowPage>0)
	{
		NowPage--;
	}

	for(int i = 0 ; i <5;i++)
	{
		Stage[i] = (i+1)+(NowPage*5);
	}
	
	StageOneEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[0])));
	StageTwoEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[1])));
	StageTirEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[2])));
	StageFourEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[3])));
	StageFiveEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[4])));
	

	if (Stage[0] > EndStage)
	{
		StageOneEnterButton->SetIsEnabled(false);
	}
	else
	{
		StageOneEnterButton->SetIsEnabled(true);
	}
	if (Stage[1] > EndStage)
	{
		StageTwoEnterButton->SetIsEnabled(false);
	}else
	{
		StageTwoEnterButton->SetIsEnabled(true);
	}
	if (Stage[2] > EndStage)
	{
		StageTirEnterButton->SetIsEnabled(false);
	}else
	{
		StageTirEnterButton->SetIsEnabled(true);
	}
	if (Stage[3] > EndStage)
	{
		StageOFourEnterButton->SetIsEnabled(false);
	}else
	{
		StageOFourEnterButton->SetIsEnabled(true);
	}
	if (Stage[4] > EndStage)
	{
		StageFiveEnterButton->SetIsEnabled(false);
	}else
	{
		StageFiveEnterButton->SetIsEnabled(true);
	}
	
}
