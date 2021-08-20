// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BulletPoolComopnent.h"

#include "MainPawn.generated.h"

UCLASS(Blueprintable)
class REAL_API AMainPawn : public APawn
{
	GENERATED_BODY()


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
	
	//�߻� �Ѵ� ���Ѵ� flag
	uint32 bCanFire : 1;

	//Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle_ShotTimerExpired;
	
/*protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;*/

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	// �Ѿ� �߻� ��ġ ����
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	// Rate float
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	// ���ǵ�
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;


	// �߻� ����
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;



	// ������ �Ѿ˹��� static const �̷��� �������
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	// �߻�
	void FireShot(FVector FireDirection);

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
