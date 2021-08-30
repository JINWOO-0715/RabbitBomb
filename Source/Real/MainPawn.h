// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BulletPoolComopnent.h"
#include "Components/WidgetComponent.h"
#include "RightWidget.h"
#include "SkillComponent.h"
#include "MainPawn.generated.h"

UCLASS(Blueprintable)
class REAL_API AMainPawn : public APawn
{
	GENERATED_BODY()

	UFUNCTION()
			virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//스테틱 메쉬 컴포넌트
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;

	// 카메라 컴포넌트
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	//카메라 스프링 컴포넌트
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere,Category="Spawner")
	UBulletPoolComopnent* ObjectPooler;
	
	UPROPERTY(EditAnywhere)
	USkillComponent* SkillContainer;


	
	// 플레이어 최대경험치
	UPROPERTY()
	float MaxEXP =100.f;
	// 플레이어 현재경험치
	UPROPERTY()
	float NowEXP =0.f;
	
	// 공격속도
	UPROPERTY()
	float FireRate = 1.f;

	// 이동속도 스피드
	UPROPERTY()
	float MoveSpeed;
	
	// 공격력
	UPROPERTY()
	float BulletPower=50.f;
	//HP
	UPROPERTY()
	float MaxHP =100.f;
	//발사 한다 한한다 flag
	uint32 bCanFire : 1;

	//타이머 핸들
	FTimerHandle TimerHandle_ShotTimerExpired;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	UPROPERTY(EditAnywhere,Category="Spawner")
		class USkillComponent* SkillComp;
	
	// 총알 발사 위치 벡터
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool PressedFireButton;

	// 이속설정
	UFUNCTION(BlueprintCallable)
	void SetMoveSpeed(float mMoveSpeed);

	UFUNCTION(BlueprintCallable)
	void SetMaxHp(float mMaxHP);

	UFUNCTION(BlueprintCallable)
	void SetFireRate(float mFireRate);
	
	UFUNCTION(BlueprintCallable)
	void SetBulletPower(float mBulletPower);
	
	
	// 발사 사운드
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;


	// //위젯
	// UPROPERTY(EditAnywhere)
	//  TSubclassOf<UUserWidget> PlayerRightWidgetClass;
	//
	//
	// UPROPERTY(VisibleInstanceOnly)
	// class URightWidget* PlayerRightWidget;


	
	// 움직임 총알방향 static const 이런건 배워야함
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	// 발사
	UFUNCTION(BlueprintCallable)
	void FireShot(FVector FireDir);
	
	//경험치 획득
	UFUNCTION(BlueprintCallable)
	void GetExperience(float Exp);

	UFUNCTION(BlueprintCallable)
	void Dash();

	//이건 발사타이머.
	void ShotTimerExpired();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	



	
	//HP 
	FORCEINLINE	float GetMaxHp() const {return MaxHP;};
	//공속 
	FORCEINLINE	float GetFireRate() const {return FireRate;};
	//공격력 
	FORCEINLINE	float Get() const {return BulletPower;};
	
	//이속 
	FORCEINLINE	float GetMoveSpeed() const {return MoveSpeed;};
	// 총알 공격력 리턴
	FORCEINLINE	float GetBulletPower() const {return BulletPower;};
	// 메시 리턴
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	// 카메라 리턴
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	// 스프링암 리턴
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
