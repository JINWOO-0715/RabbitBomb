// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPawn.h"

#include "ChooseSkillWidget.h"
#include "MainInGameWidget.h"
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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MainMesh(
		TEXT("/Game/Mesh/MainCharacterMesh.MainCharacterMesh"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	ShipMeshComponent->SetStaticMesh(MainMesh.Object);

	BulletAttackPattern = CreateDefaultSubobject<UBulletAttackPattern>(TEXT("Attack"));
	
	static ConstructorHelpers::FClassFinder<UMainInGameWidget> HPBarAsset(
		TEXT("/Game/BP/HPBar"));
	PlayerHPWidgetClass = HPBarAsset.Class;
	


	//사운드
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/Sound/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;
	
	//카메라 스프링
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// 카메라 만들기
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SkillComp = CreateDefaultSubobject<USkillComponent>(TEXT("Skill"));


	ItemGettingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GetItemCullusion"));
	ItemGettingSphere->SetupAttachment(RootComponent);
	ItemGettingSphere->InitSphereRadius(400.f);
	ItemGettingSphere->OnComponentBeginOverlap.AddDynamic(this, &AMainPawn::OnOverlapBegin);
	
	

	Tags.Add("Player");

	// Movement
	MoveSpeed = 700.0f;


	//경험치
	NowEXP = 100.f;
	MaxEXP = 100.f;

	//스텟 (HP 공격력)
	MaxHP = 100.f;
	BulletPower = 50.5f;

	// Weapon


	NumberOfShotBullet = 1;
	GunOffset = FVector(80.f, 0.f, 0.f);
	FireRate = 0.5f;
	bCanFire = true;
}



void AMainPawn::SetMoveSpeed(float mMoveSpeed)
{
	MoveSpeed = mMoveSpeed;
}

void AMainPawn::SetMaxHp(float mMaxHP)
{
	MaxHP = mMaxHP;
}

void AMainPawn::SetFireRate(float mFireRate)
{


	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("sucess"));
	FireRate = mFireRate;
}

void AMainPawn::SetBulletPower(float mBulletPower)
{
	BulletPower = mBulletPower;
}


void AMainPawn::BackButton()
{
	//PlayerScoreWidget->ShowButton();
}
//
// void AMainPawn::SetScoreText()
// {
// 	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
// 	
// 	if(PlayerScoreWidget!=nullptr)
// 	{
// 		PlayerScoreWidget->SetRemainMonsterText(GameInstanceRef->MonsterCount);
// 		PlayerScoreWidget->SetNowWaveText(GameInstanceRef->NowWave,GameInstanceRef->GoalWave);
// 	}
// }

//// Called when the game starts or when spawned 비긴플레이 쓸일있으면 사용
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();
	SkillComp->OwnerActor = this;
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GetWorld()->GetName() == FString("MainLevel"))
	{
		PlayerHPWidget = Cast<UMainInGameWidget>(CreateWidget(GetWorld(), PlayerHPWidgetClass));
		
		if (PlayerHPWidget != nullptr)
		{
			PlayerHPWidget->AddToViewport();
			
			// PlayerSkillChooseWidget->Player=this;
			// PlayerRightWidget->AddToViewport();
		}
	
		
		SetMaxHPToLevel(GameInstanceRef->PlayerHPLevel);
		SetPowerToLevel(GameInstanceRef->PlayerPowerLevel);
		SetSpeedUPToLevel(GameInstanceRef->PlayerSpeedLevel);
		SetFireRate(GameInstanceRef->PlayerFireRateLevel);
		SetFireRateToLevel(GameInstanceRef->PlayerFireRateLevel);
		
	}
}

// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	// 움직일 방향 찾기
	float ForwardValue = GetInputAxisValue(MoveForwardBinding); // 앞 +1.0 뒤 -1.0
	if(ForwardValue<0.f)
	{
		ForwardValue=-1.0f;
	}
	if(ForwardValue>0.f)
	{
		ForwardValue=1.0f;
	}
	float RightValue = GetInputAxisValue(MoveRightBinding); //오 1.0 왼-1.0

	if(RightValue<0.f)
	{
		RightValue=-1.0f;
	}
	if(RightValue>0.f)
	{
		RightValue=1.0f;
	}
	
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

	// 발사할위치 벡터
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	FireShot(FireDirection);
	// 발사
	// if(PressedFireButton)
	// {
	// 	FireShot(FireDirection);
	// }
}


// 데미지 받는 함수 오버라이드 사용
float AMainPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                            AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::SanitizeFloat(NowHP));
	//Engine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("HIT"));
	NowHP -= Damage;
	PlayerHPWidget->HPBar->SetPercent(NowHP / MaxHP);
	ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), gm->HitedParticle, GetActorLocation(),FRotator(0.f,0.f,0.f),FVector(3.f,3.f,3.f));
	//gm->LoseSound
	// 사망 죽음
	UGameplayStatics::PlaySoundAtLocation(this, gm->LoseSound2, GetActorLocation());
	if (NowHP < 0.f)
	{
		ReturnToTitle();
	}

	return Damage;
}
void AMainPawn::ReturnToTitle()
{
	UGameplayStatics::OpenLevel(this, FName("TitleLevel"), true);
}

void AMainPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Line"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		
	}
	if (OtherActor->ActorHasTag("Item"))
	{
		
		AItemActor* ItemActor = Cast<AItemActor>(OtherActor);
		ItemActor->isFollowing = true;
	}
}

void AMainPawn::FireShot(FVector FireDir)
{
	if (bCanFire)
	{
		if (FireDir.SizeSquared() > 0.0f)
		{	bCanFire = false; // 끊고
			const FRotator FireRotation = FireDir.Rotation();

			UWorld* const World = GetWorld();

			if (NumberOfShotBullet == 1)
			{
				BulletAttackPattern->OneStraightShot(FireDir);
			}
			else if (NumberOfShotBullet == 3)
			{
				BulletAttackPattern->ThreeStraightShot(FireDir);
			}
			else if (NumberOfShotBullet == 5)
			{
				BulletAttackPattern->FiveStraightShot(FireDir);
			}
			
		
			// 타이머 작동
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMainPawn::ShotTimerExpired,
			                                  FireRate);
			// 소리재생
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

		}
	}
}


void AMainPawn::GetExperience(float Exp)
{
	NowEXP += Exp;
	float persent = (NowEXP / MaxEXP);

	if (persent >= 1.f)
	{
		ARealGameModeBase* gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
		if (gm->PlayerSkillChooseWidget)
		{
			
			gm->PlayerSkillChooseWidget->AddToViewport();
			//gm->PlayerSkillChooseWidget->SetRandomSkill();
			// 게임 중지 넣어함
			//PlayerRightWidget->SetPlayer();
			//UE_LOG(LogTemp, Warning, TEXT("sucess wiget"));
		}
		// 스킬 선택
		//

		NowEXP = 0.f;
		MaxEXP = 2 * MaxEXP;

		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		if (MyPlayer != NULL)
		{
			MyPlayer->SetPause(true);
		}
	}
}


// void AMainPawn::Dash()
// {
// 	FHitResult Hit(1.f);
// 	const FVector TeleportPoint = GetActorLocation() + (GetActorForwardVector() * 300.f);
//
// 	SetActorLocation(TeleportPoint, true, &Hit);
// }

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
	InputComponent->BindAction("Back", EInputEvent::IE_Released, this, &AMainPawn::BackButton);
}

void AMainPawn::SetMaxHPToLevel(int HpLevel)
{


    MaxHP = MaxHP+(MaxHP*0.3*HpLevel);
	NowHP = MaxHP;
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->Save();
	
}
void AMainPawn::SetFireRateToLevel(int FireRateLevel)
{
	FireRate = FireRate-(FireRate*0.2*FireRateLevel);
	if(FireRate<0.1)
	{
		FireRate=0.1f;
	}
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->Save();
}

void AMainPawn::SetPowerToLevel(int PowerLevel)
{
	BulletPower = BulletPower+(BulletPower*0.2*PowerLevel);
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->Save();
	
}

void AMainPawn::SetSpeedUPToLevel(int mSpeedUp)
{
	MoveSpeed = MoveSpeed+(MoveSpeed*0.1*mSpeedUp);
	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	gm->Save();
}


void AMainPawn::UpHp(float mUphp)
{
	NowHP += mUphp;
	
	PlayerHPWidget->HPBar->SetPercent(NowHP / MaxHP);
}

void AMainPawn::UpPlayerCoin(int mUpcoinNum)
{

	ARealGameModeBase* const gm = (ARealGameModeBase*)GetWorld()->GetAuthGameMode();
	auto* GameInstanceRef = Cast<URabbitBombGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	GameInstanceRef->PlayerHasCoin += mUpcoinNum;
	gm->Save();
}


void AMainPawn::SetNumberOfShotBullet(float mNumOfBullet)
{

	NumberOfShotBullet = int(mNumOfBullet);
}
