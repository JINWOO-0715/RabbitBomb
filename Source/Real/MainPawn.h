// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// #include "RightWidget.h"
// #include "ItemActor.h"
// #include "BulletPoolComopnent.h"
#include "Components/WidgetComponent.h"
#include "Bullet.h"
#include "ScoreWidget.h"

#include "Engine/Classes/Components/SphereComponent.h"

#include "SkillComponent.h"
#include "MainPawn.generated.h"

UCLASS(Blueprintable)
class REAL_API AMainPawn : public APawn
{
	GENERATED_BODY()

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;

	//스테틱 메쉬 컴포넌트
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	// 카메라 컴포넌트
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	//카메라 스프링 컴포넌트
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* ItemGettingSphere;

	UFUNCTION()

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, Category="Spawner")
	class UBulletPoolComopnent* ObjectPooler;

	UPROPERTY(EditAnywhere)
	class USkillComponent* SkillContainer;



	UPROPERTY()
	int FireRatelevel = 1;


	UPROPERTY()
	int MoveSpeedlevel = 1;

	
	UPROPERTY()
	int BulletPowerlevel = 1;


	UPROPERTY()
	int MaxHPlevel = 1;

	// 플레이어 최대경험치
	UPROPERTY()
	float MaxEXP = 100.f;
	// 플레이어 현재경험치
	UPROPERTY()
	float NowEXP = 0.f;

	// 공격속도
	UPROPERTY(EditAnywhere)
	float FireRate = 1.f;

	// 이동속도 스피드
	UPROPERTY()
	float MoveSpeed;

	// 공격력
	UPROPERTY()
	float BulletPower = 50.f;
	//HP
	UPROPERTY()
	float MaxHP = 100.f;

	UPROPERTY()
	float NowHP = 100.f;

	UPROPERTY()
	int NumberOfShotBullet = 1;


	int PlayerCoin = 1000000;

	//발사 한다 한한다 flag
	uint32 bCanFire : 1;
    void BackButton();
	//타이머 핸들
	FTimerHandle TimerHandle_ShotTimerExpired;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	UPROPERTY(EditAnywhere, Category="Spawner")
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

	
	UFUNCTION(BlueprintCallable)
	void SetMoveSpeedLevel(int mMoveSpeedLevel);
	UFUNCTION(BlueprintCallable)
	void SetMaxHpLevel(int mMaxHpLevel);
	UFUNCTION(BlueprintCallable)
	void SetFireRateLevel(int mFireRateLevel);
	UFUNCTION(BlueprintCallable)
	void SetBulletPowerLevel(int mBulletPowerLevel);
	
	// 발사 사운드
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;


	// //위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayerHPWidgetClass;
	//
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMainInGameWidget* PlayerHPWidget;


	// //위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	//
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UScoreWidget* PlayerScoreWidget;
	

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


	// 스텟 레벨업
	void MaxHpUP(float mUpMaxHp);
	void UpHp(float mUphp);
	void PowerUP(float mPowerUp);
	void SpeedUP(float mSpeedUp);
	void FireRateUP(float mFireRate);
	void UpPlayerCoin(int mUpcoinNum);
	void SetPlayerCoin(int mCoin);
	//공격력 
	FORCEINLINE float Get() const { return BulletPower; };

	void SetNumberOfShotBullet(float mNumOfBullet);



	FORCEINLINE int GetFireRatelevel() const { return FireRatelevel; };
	FORCEINLINE int GetMoveSpeedlevel() const { return MoveSpeedlevel; };
	FORCEINLINE int GetBulletPowerlevel() const { return BulletPowerlevel; };
	FORCEINLINE int GetMaxHPlevel() const { return MaxHPlevel; };


	// 발사수
	FORCEINLINE float GetNumOfShotBullet() const { return NumberOfShotBullet; };
	//HP 
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetNowHp() const { return NowHP; };
	//HP 
	FORCEINLINE float GetMaxHp() const { return MaxHP; };
	//공속 
	FORCEINLINE float GetFireRate() const { return FireRate; };
	//공격력 
	FORCEINLINE int GetCoin() const { return PlayerCoin; };

	//이속 
	FORCEINLINE float GetMoveSpeed() const { return MoveSpeed; };
	// 총알 공격력 리턴
	FORCEINLINE float GetBulletPower() const { return BulletPower; };
	// 메시 리턴
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	// 카메라 리턴
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	// 스프링암 리턴
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
