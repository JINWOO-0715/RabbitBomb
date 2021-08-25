// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BulletPoolComopnent.h"
#include "Components/WidgetComponent.h"
#include "RightWidget.h"

#include "MainPawn.generated.h"

UCLASS(Blueprintable)
class REAL_API AMainPawn : public APawn
{
	GENERATED_BODY()

	UFUNCTION()
			virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//����ƽ �޽� ������Ʈ
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;

	// ī�޶� ������Ʈ
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	//ī�޶� ������ ������Ʈ
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere,Category="Spawner")
	UBulletPoolComopnent* ObjectPooler;
	
	// �÷��̾� �ִ����ġ
	UPROPERTY()
	float MaxEXP =100.f;
	// �÷��̾� �������ġ
	UPROPERTY()
	float NowEXP =0.f;
	
	//�߻� �Ѵ� ���Ѵ� flag
	uint32 bCanFire : 1;

	//Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle_ShotTimerExpired;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	// �Ѿ� �߻� ��ġ ����
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	// ���ݼӵ�
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate = 3.f;

	// �̵��ӵ� ���ǵ�
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;
	
	// ���ݷ�
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float BulletPower=50.f;
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		bool PressedFireButton;

	// �÷��̾� �ִ�ü��
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MaxHP =100.f;

	// �߻� ����
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;

	

	

	//����
	UPROPERTY(EditAnywhere)
	 TSubclassOf<UUserWidget> PlayerRightWidgetClass;

	
	UPROPERTY(VisibleInstanceOnly)
	class URightWidget* PlayerRightWidget;

	// ������ �Ѿ˹��� static const �̷��� �������
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	// �߻�
	UFUNCTION(BlueprintCallable)
	void FireShot();
	
	//����ġ ȹ��
	UFUNCTION(BlueprintCallable)
	void GetExperience(float Exp);
	
	void Dash();

	//�̰� �߻�Ÿ�̸�.
	void ShotTimerExpired();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �޽� ����
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	// ī�޶� ����
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	// �������� ����
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
