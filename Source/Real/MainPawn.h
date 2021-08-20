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
	
	//발사 한다 한한다 flag
	uint32 bCanFire : 1;

	//타이머 핸들
	FTimerHandle TimerHandle_ShotTimerExpired;
	
/*protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;*/

public:
	// Sets default values for this pawn's properties
	AMainPawn();

	// 총알 발사 위치 벡터
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	// Rate float
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	// 스피드
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;


	// 발사 사운드
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;



	// 움직임 총알방향 static const 이런건 배워야함
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

	// 발사
	void FireShot(FVector FireDirection);

	//이건 발사타이머.
	void ShotTimerExpired();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 메시 리턴
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	// 카메라 리턴
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	// 스프링암 리턴
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
