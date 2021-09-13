// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ShopWidget.h"

void UShopWidget::SetHPUptext()
{
}

void UShopWidget::SetPowerUpText()
{
	AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	
}

void UShopWidget::SetSpeedUpText()
{
}

void UShopWidget::SetFireRateUpText()
{
}
