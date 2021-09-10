// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSaveGame.h"

UPlayerSaveGame::UPlayerSaveGame()
{

	 level =1;
	
	// 공격속도
	 FireRate = 1.f;

	// 이동속도 스피드

	 MoveSpeed=500;
	
	// 공격력
	 BulletPower=50.f;
	
	//HP
	 MaxHP =100.f;
}
