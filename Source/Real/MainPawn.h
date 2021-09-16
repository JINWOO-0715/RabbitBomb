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

	//����ƽ �޽� ������Ʈ
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	// ī�޶� ������Ʈ
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	//ī�޶� ������ ������Ʈ
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

	// �÷��̾� �ִ����ġ
	UPROPERTY()
	float MaxEXP = 100.f;
	// �÷��̾� �������ġ
	UPROPERTY()
	float NowEXP = 0.f;

	// ���ݼӵ�
	UPROPERTY(EditAnywhere)
	float FireRate = 1.f;

	// �̵��ӵ� ���ǵ�
	UPROPERTY()
	float MoveSpeed;

	// ���ݷ�
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

	//�߻� �Ѵ� ���Ѵ� flag
	uint32 bCanFire : 1;
    void BackButton();
	//Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle_ShotTimerExpired;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	UPROPERTY(EditAnywhere, Category="Spawner")
	class USkillComponent* SkillComp;

	// �Ѿ� �߻� ��ġ ����
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GunOffset;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	bool PressedFireButton;


	// �̼Ӽ���
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
	
	// �߻� ����
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;


	// //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayerHPWidgetClass;
	//
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMainInGameWidget* PlayerHPWidget;


	// //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ScoreWidgetClass;
	//
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UScoreWidget* PlayerScoreWidget;
	

	// ������ �Ѿ˹��� static const �̷��� �������
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	// �߻�
	UFUNCTION(BlueprintCallable)
	void FireShot(FVector FireDir);

	//����ġ ȹ��
	UFUNCTION(BlueprintCallable)
	void GetExperience(float Exp);

	UFUNCTION(BlueprintCallable)
	void Dash();

	//�̰� �߻�Ÿ�̸�.
	void ShotTimerExpired();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// ���� ������
	void MaxHpUP(float mUpMaxHp);
	void UpHp(float mUphp);
	void PowerUP(float mPowerUp);
	void SpeedUP(float mSpeedUp);
	void FireRateUP(float mFireRate);
	void UpPlayerCoin(int mUpcoinNum);
	void SetPlayerCoin(int mCoin);
	//���ݷ� 
	FORCEINLINE float Get() const { return BulletPower; };

	void SetNumberOfShotBullet(float mNumOfBullet);



	FORCEINLINE int GetFireRatelevel() const { return FireRatelevel; };
	FORCEINLINE int GetMoveSpeedlevel() const { return MoveSpeedlevel; };
	FORCEINLINE int GetBulletPowerlevel() const { return BulletPowerlevel; };
	FORCEINLINE int GetMaxHPlevel() const { return MaxHPlevel; };


	// �߻��
	FORCEINLINE float GetNumOfShotBullet() const { return NumberOfShotBullet; };
	//HP 
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetNowHp() const { return NowHP; };
	//HP 
	FORCEINLINE float GetMaxHp() const { return MaxHP; };
	//���� 
	FORCEINLINE float GetFireRate() const { return FireRate; };
	//���ݷ� 
	FORCEINLINE int GetCoin() const { return PlayerCoin; };

	//�̼� 
	FORCEINLINE float GetMoveSpeed() const { return MoveSpeed; };
	// �Ѿ� ���ݷ� ����
	FORCEINLINE float GetBulletPower() const { return BulletPower; };
	// �޽� ����
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	// ī�޶� ����
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	// �������� ����
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
