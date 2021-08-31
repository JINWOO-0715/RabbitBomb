// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSkill.h"

#include "MainPawn.h"
#include "Kismet/GameplayStatics.h"
#include "RealGameModeBase.h"

void UBuffSkill::SetPlayerBuff(FName mSkillName)
{
	// 가지고있는 객체에게 버프를 준다.

	// 공통점
	// 데이터 테이블에서 increase count를 가져온다음
	// 적용하는데
	// 
	// skill = 광속토끼
	// // skill =
	// if(mSkillName==FName("Faster"))
	// {
	// 	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	// 	if(gm)
	// 	{
	// 		FPlayerSkillRow* SkillRowData =gm->GetPlayerSkillRowDataToNum(FName("Faster"));// 번호대신 이름
	//
	// 		AMainPawn* PlayerPawn = Cast<AMainPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// 		float TempSpeed = PlayerPawn->GetMoveSpeed();
	// 		TempSpeed*=SkillRowData->IncreaseCount;
	// 		PlayerPawn->SetMoveSpeed(TempSpeed);
	// 		
	// 	}
	//
	// }
}
