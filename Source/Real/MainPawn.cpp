// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPawn.h"
#include "Bullet.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "RealGameModeBase.h"
#include "RightWidget.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "SkillComponent.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundBase.h"

const FName AMainPawn::MoveForwardBinding("MoveForward");
const FName AMainPawn::MoveRightBinding("MoveRight");
const FName AMainPawn::FireForwardBinding("FireForward");
const FName AMainPawn::FireRightBinding("FireRight");


// Sets default values
AMainPawn::AMainPawn()
{


 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	//메인 메쉬 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MainMesh(TEXT("/Game/Mesh/MainCharacterMesh.MainCharacterMesh"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);	
	
	ShipMeshComponent->SetStaticMesh(MainMesh.Object);


	//카메라 스프링
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// 카메라 만들기
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	
	Tags.Add("Player");
	
	// Movement
	MoveSpeed = 1000.0f;

	
	// Weapon
	GunOffset = FVector(80.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
}


//// Called when the game starts or when spawned 비긴플레이 쓸일있으면 사용
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();

	
	//CreateWidget<URightWidget>((GetWorld(), PlayerRightWidgetClass);
	//PlayerRightWidgetClass = LoadClass<URightWidget>(this,TEXT(""));
	//PlayerRightWidget = PlayerRightWidget->GetClass();
	//PlayerRightWidget =  Cast<URightWidget>(CreateWidget(GetWorld(), PlayerRightWidgetClass));
	// PlayerRightWidget = Cast<URightWidget>(CreateWidget(GetWorld(),PlayerRightWidgetClass));
	// if(PlayerRightWidgetClass !=nullptr)
	// {
	// 	//layerRightWidget = CreateWidget<URightWidget>(GetWorld(),PlayerRightWidgetClass);
	// 	if(PlayerRightWidget)
	// 	{
	// 		PlayerRightWidget->AddToViewport();
	// 		PlayerRightWidget->Player=this;
	// 	}
	// 	// PlayerRightWidget->Player=this;
	// 	// PlayerRightWidget->AddToViewport();
	// 	
	// }
	
	
}

// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	// 움직일 방향 찾기
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding); // 앞 +1.0 뒤 -1.0
	const float RightValue = GetInputAxisValue(MoveRightBinding); //오 1.0 왼-1.0

	// 움직일 벡터 만듬.
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// 움직임 계산 ( 방향*속도*시간)
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	// 백터 방향이 0보다 크다면.
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	// // 발사할위치 벡터
	// const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	// const float FireRightValue = GetInputAxisValue(FireRightBinding);
	// const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// 발사
	if(PressedFireButton)
	{
		FireShot();
	}


}


// 데미지 받는 함수 오버라이드 사용
float AMainPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
								AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//Engine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("HIT"));
	// MonsterHP -= Damage;
	// if (MonsterHP < 0.f)
	// {
	// 	Deactivate();
	// }

	return Damage;
}

void AMainPawn::FireShot()
{
	if (bCanFire)
	{

		
		UWorld* const World = GetWorld();
		ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		ABullet* playerBullet = gm->BulletPooler->GetPooledBullet();
		playerBullet->SetOwnerActor(this);
		playerBullet->SetActorTransform(GetActorTransform());
		const FVector Movement = GetActorForwardVector() * 1000.f; // 
		playerBullet->SetVelocity(Movement);
		playerBullet->SetLifeSpan();
		playerBullet->SetActive(true);


		bCanFire = false; // 끊고

		// 타이머 작동
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMainPawn::ShotTimerExpired, FireRate);

		// 소리재생
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;
		
		// 		
		// 방향이있으면 
		// if (FireDir.SizeSquared() > 0.0f)
		// {
		// 	const FRotator FireRotation = FireDir.Rotation();
		// 	
		// 	// 스폰위치잡기
		// 	FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
		//
		// 	UWorld* const World = GetWorld();
		//
		// 	//AActor* const TempActor = Cast<AActor>(this);
		// 	if (World != nullptr)
		// 	{
		// 		//FireRotation = FireRotation.GetInverse();
		// 		ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		// 		ABullet* monsterBullet = gm->BulletPooler->GetPooledBullet();
		// 		// 총알 소환
		// 		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FireRotation.ToString());
		// 		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FireDir.ToString());
		// 		monsterBullet->SetOwnerActor(this);
		// 		//SpawnLocation*=1.2f;
		// 		monsterBullet->SetActorLocation(SpawnLocation);
		// 		monsterBullet->SetActorRotation(FireRotation.GetInverse());
		// 		FireDir.Normalize();
		// 		const FVector Movement = FireDir * 1000.f  ;// 
		// 		monsterBullet->SetVelocity(Movement);
		// 		monsterBullet->SetLifeSpan();
		// 		monsterBullet->SetActive(true);
		// 	}
		//
		// 	bCanFire = false;// 끊고
		//
		// 	// 타이머 작동
		// 	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMainPawn::ShotTimerExpired, FireRate);
		//
		// 	// 소리재생
		// 	if (FireSound != nullptr)
		// 	{
		// 		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		// 	}
		//
		// 	bCanFire = false;
		// }
	}

}

void AMainPawn::GetExperience(float Exp)
{
	NowEXP+=Exp;
	float persent = (NowEXP/MaxEXP);
	if(persent>=1.f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("LevelUp"));
		NowEXP=0.f;
		MaxEXP*=1.2f;
	}
}

void AMainPawn::Dash()
{
	FHitResult Hit(1.f);
	const FVector TeleportPoint = GetActorLocation() +( GetActorForwardVector()*300.f);

	SetActorLocation(TeleportPoint,true,&Hit);
}

void AMainPawn::ShotTimerExpired()
{
	bCanFire = true;
}
// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);

}



