// Fill out your copyright notice in the Description page of Project Settings.


#include "RightWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainPawn.h"
#include "components/Button.h"


void URightWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FireButton->OnPressed.AddDynamic(this, &URightWidget::FireOn);
	FireButton->OnReleased.AddDynamic(this, &URightWidget::FireOff);
	DashButton->OnPressed.AddDynamic(this, &URightWidget::DashOn);
	//DashButton->OnReleased.AddDynamic(this, &URightWidget::FireOff);
}

void URightWidget::DashOn()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	if(!Player)
	{
		SetPlayer();
	}
	if(Player)
	{
		Player->Dash();;
	}
}



void URightWidget::FireOn()
{
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	if (!Player)
	{
		SetPlayer();
	}
	if (Player)
	{
		//UWorld* const World = GetWorld();
		// 	
		// 	World()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMainPawn::ShotTimerExpired, FireRate);
		Player->PressedFireButton = true;
		//Player->FireShot();
	}
}

void URightWidget::FireOff()
{
	if (!Player)
	{
		SetPlayer();
	}
	if (Player)
	{
		//UWorld* const World = GetWorld();
		// 	
		// 	World()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMainPawn::ShotTimerExpired, FireRate);
		Player->PressedFireButton = false;
		//Player->FireShot();
	}
}

//
void URightWidget::SetPlayer()
{
	AMainPawn* getMainPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player = getMainPawn;
}
