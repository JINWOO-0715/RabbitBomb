// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopWidget.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpUpButton->OnPressed.AddDynamic(this, &UShopWidget::HpUpFun);
	FireRateUpButton->OnPressed.AddDynamic(this, &UShopWidget::FireRateUpFun);
	PowerUpButton->OnPressed.AddDynamic(this, &UShopWidget::PowerUpFun);
	SpeedUpButton->OnPressed.AddDynamic(this, &UShopWidget::SpeedUpFun);

	
	//AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), GameInstanceRef->PlayerHasCoin)));

	
	HPUptext->SetText(FText::FromString( FString::Printf(TEXT("HP\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerHPLevel, GameInstanceRef->PlayerHPLevel*200)));
	PowerUpText->SetText(FText::FromString( FString::Printf(TEXT("Power\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerPowerLevel, GameInstanceRef->PlayerPowerLevel*200)));
	SpeedUpText->SetText(FText::FromString( FString::Printf(TEXT("Speed\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerSpeedLevel, GameInstanceRef->PlayerSpeedLevel*200)));
	FireRateUpText->SetText(FText::FromString( FString::Printf(TEXT("FireRate\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerFireRateLevel, GameInstanceRef->PlayerFireRateLevel*200)));
}


void UShopWidget::HpUpFun()
{
	
	//AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(GameInstanceRef->PlayerHasCoin >= GameInstanceRef->PlayerHPLevel*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(GameInstanceRef->PlayerHPLevel));
		GameInstanceRef->PlayerHasCoin-=200*GameInstanceRef->PlayerHPLevel;
		GameInstanceRef->PlayerHPLevel++;
	
			
	}
	// 1.2배씩 상승한다 hp가
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"),GameInstanceRef->PlayerHasCoin)));
	HPUptext->SetText(FText::FromString( FString::Printf(TEXT("HP\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerHPLevel,GameInstanceRef->PlayerHPLevel*200)));
}

void UShopWidget::PowerUpFun()
{
	//AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(GameInstanceRef->PlayerHasCoin >= GameInstanceRef->PlayerPowerLevel*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(GameInstanceRef->PlayerPowerLevel));
		GameInstanceRef->PlayerHasCoin-=200*GameInstanceRef->PlayerPowerLevel;
		GameInstanceRef->PlayerPowerLevel++;
	}
	
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"),GameInstanceRef->PlayerHasCoin)));
	PowerUpText->SetText(FText::FromString( FString::Printf(TEXT("Power\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerPowerLevel, GameInstanceRef->PlayerPowerLevel*200)));
}

void UShopWidget::SpeedUpFun()
{
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(GameInstanceRef->PlayerHasCoin >= GameInstanceRef->PlayerSpeedLevel*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(GameInstanceRef->PlayerSpeedLevel));
		GameInstanceRef->PlayerHasCoin-=200*GameInstanceRef->PlayerSpeedLevel;
		GameInstanceRef->PlayerSpeedLevel++;
	}

	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), GameInstanceRef->PlayerHasCoin)));
	SpeedUpText->SetText(FText::FromString( FString::Printf(TEXT("Speed\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerSpeedLevel ,GameInstanceRef->PlayerSpeedLevel*200)));
}

void UShopWidget::FireRateUpFun()
{
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(GameInstanceRef->PlayerHasCoin >= GameInstanceRef->PlayerFireRateLevel*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(GameInstanceRef->PlayerPowerLevel));
		GameInstanceRef->PlayerHasCoin-=200*GameInstanceRef->PlayerFireRateLevel;
		GameInstanceRef->PlayerFireRateLevel++;
	}
	// 1.2배씩 상승한다 hp가
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), GameInstanceRef->PlayerHasCoin)));
	FireRateUpText->SetText(FText::FromString( FString::Printf(TEXT("FireRate\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerFireRateLevel, GameInstanceRef->PlayerFireRateLevel*200)));
}

void UShopWidget::SetText()
{
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	HPUptext->SetText(FText::FromString( FString::Printf(TEXT("HP\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerHPLevel, GameInstanceRef->PlayerHPLevel*200)));
	PowerUpText->SetText(FText::FromString( FString::Printf(TEXT("Power\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerPowerLevel, GameInstanceRef->PlayerPowerLevel*200)));
	SpeedUpText->SetText(FText::FromString( FString::Printf(TEXT("Speed\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerSpeedLevel, GameInstanceRef->PlayerSpeedLevel*200)));
	FireRateUpText->SetText(FText::FromString( FString::Printf(TEXT("FireRate\nNow Level : %d \nNeed Coin : %d"),GameInstanceRef->PlayerFireRateLevel, GameInstanceRef->PlayerFireRateLevel*200)));

}
