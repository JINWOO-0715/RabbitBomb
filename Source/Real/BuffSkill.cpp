// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSkill.h"

#include "MainPawn.h"
#include "Kismet/GameplayStatics.h"
#include "RealGameModeBase.h"

void UBuffSkill::SetPlayerBuff(FName mSkillName)
{
	// �������ִ� ��ü���� ������ �ش�.

	// ������
	// ������ ���̺��� increase count�� �����´���
	// �����ϴµ�
	// 
	// skill = �����䳢
	// // skill =
	// if(mSkillName==FName("Faster"))
	// {
	// 	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	// 	if(gm)
	// 	{
	// 		FPlayerSkillRow* SkillRowData =gm->GetPlayerSkillRowDataToNum(FName("Faster"));// ��ȣ��� �̸�
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
