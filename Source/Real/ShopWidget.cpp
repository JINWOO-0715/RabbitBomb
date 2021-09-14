// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ShopWidget.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpUpButton->OnPressed.AddDynamic(this, &UShopWidget::HpUpFun);
	FireRateUpButton->OnPressed.AddDynamic(this, &UShopWidget::FireRateUpFun);
	PowerUpButton->OnPressed.AddDynamic(this, &UShopWidget::PowerUpFun);
	SpeedUpButton->OnPressed.AddDynamic(this, &UShopWidget::SpeedUpFun);

	
	AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), player->GetCoin())));

	
	HPUptext->SetText(FText::FromString( FString::Printf(TEXT("HP\nNow Level : %d \nNeed Coin : %d"),player->GetMaxHPlevel(), player->GetMaxHPlevel()*200)));
	PowerUpText->SetText(FText::FromString( FString::Printf(TEXT("Power\nNow Level : %d \nNeed Coin : %d"),player->GetBulletPowerlevel(), player->GetBulletPowerlevel()*200)));
	SpeedUpText->SetText(FText::FromString( FString::Printf(TEXT("Speed\nNow Level : %d \nNeed Coin : %d"),player->GetMoveSpeedlevel(), player->GetMoveSpeedlevel()*200)));
	FireRateUpText->SetText(FText::FromString( FString::Printf(TEXT("FireRate\nNow Level : %d \nNeed Coin : %d"),player->GetFireRatelevel(), player->GetFireRatelevel()*200)));
}


void UShopWidget::HpUpFun()
{
	
	AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(player->GetCoin() >= player->GetMaxHPlevel()*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(player->GetMaxHPlevel()));
		player->MaxHpUP(1.2f);	
	}
	// 1.2배씩 상승한다 hp가
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), player->GetCoin())));
	HPUptext->SetText(FText::FromString( FString::Printf(TEXT("HP\nNow Level : %d \nNeed Coin : %d"),player->GetMaxHPlevel(), player->GetMaxHPlevel()*200)));
}

void UShopWidget::PowerUpFun()
{
	AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(player->GetCoin() >= player->GetBulletPowerlevel()*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(player->GetMaxHPlevel()));
		player->PowerUP(1.2f);	
	}
	// 1.2배씩 상승한다 hp가
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), player->GetCoin())));
	PowerUpText->SetText(FText::FromString( FString::Printf(TEXT("Power\nNow Level : %d \nNeed Coin : %d"),player->GetBulletPowerlevel(), player->GetBulletPowerlevel()*200)));
}

void UShopWidget::SpeedUpFun()
{
	AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(player->GetCoin() >= player->GetMoveSpeedlevel()*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(player->GetMaxHPlevel()));
		player->SpeedUP(1.2f);	
	}
	// 1.2배씩 상승한다 hp가
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), player->GetCoin())));
	SpeedUpText->SetText(FText::FromString( FString::Printf(TEXT("Speed\nNow Level : %d \nNeed Coin : %d"),player->GetMoveSpeedlevel(), player->GetMoveSpeedlevel()*200)));
}

void UShopWidget::FireRateUpFun()
{
	AMainPawn* player =Cast<AMainPawn>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(player->GetCoin() >= player->GetFireRatelevel()*200)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(player->GetMaxHPlevel()));
		player->FireRateUP(1.2f);	
	}
	// 1.2배씩 상승한다 hp가
	RemainCoinText->SetText(FText::FromString( FString::Printf(TEXT("RemainCoin : %d"), player->GetCoin())));
	FireRateUpText->SetText(FText::FromString( FString::Printf(TEXT("FireRate\nNow Level : %d \nNeed Coin : %d"),player->GetFireRatelevel(), player->GetFireRatelevel()*200)));
}

