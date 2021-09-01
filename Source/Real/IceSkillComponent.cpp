// Fill out your copyright notice in the Description page of Project Settings.


#include "IceSkillComponent.h"
#include "RealGameModeBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UIceSkillComponent::UIceSkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bCanFire =true;
	SkillCoolTime=1.f;
	// ...
}


// Called when the game starts
void UIceSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UIceSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
	IceCircleAttack();
}

void UIceSkillComponent::IceCircleAttack()
{
	if (bCanFire)
	{
		UWorld* const World = GetWorld();

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &UIceSkillComponent::ShotTimerExpired,
		                                  SkillCoolTime);
		ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		ABullet* IceTypeBullet = gm->BulletPooler->GetPooledBullet();

		// 얼음 소환해서 공격하기
		float parameter = -2.2f;

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(3));
		for (int i = 0; i < 4; i++)
		{
			IceTypeBullet->BulletType = FName("Ice");
			IceTypeBullet = gm->BulletPooler->GetPooledBullet();
			IceTypeBullet->SetOwnerActor(OwnerActor);
			IceTypeBullet->SetActorLocation(OwnerActor->GetActorLocation());
			//IceTypeBullet->SetActorRotation(FireRotation.GetInverse());
			FVector FireDir = -(OwnerActor->GetActorForwardVector());

			FVector RotationVector(FireDir.X * cos(parameter) - FireDir.Y * sin(parameter),
			                       FireDir.X * sin(parameter) + FireDir.Y * cos(parameter), 0.f);
			RotationVector.Normalize();
			parameter += 1.7f;
			const FVector Movement = RotationVector * 1000.f; // 
			IceTypeBullet->SetVelocity(Movement);
			IceTypeBullet->SetLifeSpan();
			IceTypeBullet->SetActive(true);
		}
		bCanFire = false;
	}
}

void UIceSkillComponent::ShotTimerExpired()
{
	bCanFire = true;
}
