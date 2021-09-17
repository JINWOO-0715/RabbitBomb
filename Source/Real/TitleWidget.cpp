// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"

#include "RabbitBombGameInstance.h"
#include "Components/VerticalBox.h"


// add to 뷰포트시 출력
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

	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[0])));
	ChooseStage=Stage[0];
	ShowEnterBox();
}

void UTitleWidget::ClickStageTwoButton()
{
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[1])));
	ChooseStage=Stage[1];
	ShowEnterBox();
}

void UTitleWidget::ClickStageTirButton()
{
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[2])));
	ChooseStage=Stage[2];
	ShowEnterBox();		

}

void UTitleWidget::ClickStageFourButton()
{
	EnterMapNameText->SetText(FText::FromString( FString::Printf(TEXT("Enter Stage %d ?"),Stage[3])));
	ChooseStage=Stage[3];
	ShowEnterBox();
}

void UTitleWidget::ClickStageFiveButton()
{
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
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GameInstanceRef)
	{
		GameInstanceRef->NowStage =ChooseStage;
	}
	UGameplayStatics::OpenLevel(this, FName("MainLevel"), true);
}

void UTitleWidget::ShowEnterBox()
{
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
	// 22단계 / 5 4

	NowPage++;
	for(int i = 0 ; i <5;i++)
	{
		Stage[i] = (i+1)+(NowPage*5);
	}
	StageOneEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[0])));
	StageTwoEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[1])));
	StageTirEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[2])));
	StageFourEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[3])));
	StageFiveEnterText->SetText(FText::FromString( FString::Printf(TEXT("Stage %d"),Stage[4])));
}

void UTitleWidget::DecreasePage()
{
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
}
