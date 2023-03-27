// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Penguin.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
APlayer_Penguin::APlayer_Penguin()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetRelativeLocation(FVector(0, 0, 40));
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Ammo = 10;
	MaxAmmo = 10;
	MovementSpeed = 1000;
	Lives = 5;
	/*CanRestart = false;*/
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	checkRestart = 0;
	GameOver = false;
	InAir = false;
	LeftVector = false;
	RightVector = false;
}


// Called when the game starts or when spawned
void APlayer_Penguin::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

// Called every frame
void APlayer_Penguin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FVector ForwardVector = FVector(XInput, YInput, 0.f);
	ForwardVector.Normalize();

	FVector NewLocation = GetActorLocation() + (ForwardVector * MovementSpeed * DeltaTime);
	SetActorLocation(NewLocation);*/
	Clock += DeltaTime;
	FVector Gravity = FVector(0, 0, 96) * Clock;
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);

	if ((Controller != nullptr) && (XInput != 0.f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		SetActorLocation(GetActorLocation() + (Direction * XInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}

	if ((Controller != nullptr) && (YInput != 0.f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		SetActorLocation(GetActorLocation() + (Direction * YInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}
	if ((Controller != nullptr) && (Zinput != 0.f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Z);
		SetActorLocation(GetActorLocation() + (Direction * Zinput * MovementSpeed * DeltaTime)) ;

		SetActorRotation(Rotation);
		
	}
	if (GetActorLocation().Z > 40 && !InAir) {
		
		SetActorLocation(GetActorLocation() - (Gravity * DeltaTime));
		if (GetActorLocation().Z <= 50)
			Clock = 0;
		
	}
	if(InAir)
	{
		if (GetActorLocation().Z >= 30)
		{
			
			FVector Jump = FVector(0, 0, 200);
			
			SetActorLocation(GetActorLocation() + (Jump * DeltaTime));

		}
		if (Clock >= 1.5f) {
			InAir = false;
			
		}
		
		
	}
	/*if(LeftVector)
		{
			FVector LeftCounter = FVector(2, 200, 0);
			SetActorLocation(GetActorLocation() - LeftCounter * DeltaTime);
		}

		if(RightVector)
		{
			FVector RightCounter = FVector(2, 200, 0);
			SetActorLocation(GetActorLocation() + RightCounter * DeltaTime);

		}*/
}

//FVector GetActorHeight()
//{
//	FVector Gravity = FVector(0, 0, 2);
//	FVector Jump = FVector(0, 0, 10);
//	return (Jump - Gravity * DeltaTime);
//}

// Called to bind functionality to input
void APlayer_Penguin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Triggered, this, &APlayer_Penguin::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Triggered, this, &APlayer_Penguin::Right);
		EnhanceInputCom->BindAction(UpInput, ETriggerEvent::Triggered, this, &APlayer_Penguin::Up);


		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Completed, this, &APlayer_Penguin::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Completed, this, &APlayer_Penguin::Right);
		EnhanceInputCom->BindAction(UpInput, ETriggerEvent::Completed, this, &APlayer_Penguin::Up);

		EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Triggered, this, &APlayer_Penguin::MouseX);
		EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Triggered, this, &APlayer_Penguin::MouseY);

		EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Completed, this, &APlayer_Penguin::MouseX);
		EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Completed, this, &APlayer_Penguin::MouseY);

		EnhanceInputCom->BindAction(ShootInput, ETriggerEvent::Started, this, &APlayer_Penguin::Shoot);
		EnhanceInputCom->BindAction(ReloadInput, ETriggerEvent::Started, this, &APlayer_Penguin::Reload);
		EnhanceInputCom->BindAction(RestartInput, ETriggerEvent::Started, this, &APlayer_Penguin::Restart);
	}
}


void APlayer_Penguin::MouseX(const FInputActionValue& input)
{
	Yaw = input.Get<float>();
	AddControllerYawInput(Yaw);
}

void APlayer_Penguin::MouseY(const FInputActionValue& input)
{
	Pitch = input.Get<float>();
	AddControllerPitchInput(Pitch);
}

void APlayer_Penguin::Forward(const FInputActionValue& input)
{
	XInput = input.Get<float>();
}
void APlayer_Penguin::Up(const FInputActionValue& input)
{
	InAir = true;
	
}
void APlayer_Penguin::Right(const FInputActionValue& input)
{
	YInput = input.Get<float>();

	
		
}

void APlayer_Penguin::HitByTarget()
{
	Lives--;
	if (Lives <= 0)
	{
		/*GameOver = true;*/
		return;
		// TODO : Game over
	}
}



void APlayer_Penguin::Shoot(const FInputActionValue& input)
{
	if (Ammo > 0)
	{
		Ammo--;

		if (Controller != nullptr)
		{
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0.f;
			Rotation.Roll = 0.f;
			

			FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

			GetWorld()->SpawnActor<AActor>(BP_Bullet,                                        // What to spawn
				GetActorLocation() + (Direction * 50.f), // Location
				Rotation);                                        // Rotation
		}
	}
}

void APlayer_Penguin::Reload(const FInputActionValue& input)
{
	Ammo = MaxAmmo;
}

void APlayer_Penguin::Restart(const FInputActionValue& input)
{
	/*CanRestart = true;
	checkRestart = 1;*/
}
