// Fill out your copyright notice in the Description page of Project Settings.


#include "Penguin.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Bullet.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
APenguin::APenguin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Ammo = 10;
	MaxAmmo = 10;
	MovementSpeed = 1000;
	Lives = 5;
	/*CanRestart = false;*/
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	GameOver = false;
	InAir = false;
	LeftVector = false;
	RightVector = false;
	Velocity = FVector(0,0, 0);
	Acceleration = FVector(20, 0, 0);
	RightSlide = FVector(0, 20, 0);
}

// Called when the game starts or when spawned
void APenguin::BeginPlay()
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
void APenguin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Clock += DeltaTime;

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

	
	/*if (InAir)
	{
			FVector Jump = FVector(0, 0, 200);

			SetActorLocation(GetActorLocation() + (Jump * DeltaTime));*/

		
	if (!InAir)
		Clock = 0;
	
		


	//Adds velocity
	
	
}

// Called to bind functionality to input
void APenguin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Triggered, this, &APenguin::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Triggered, this, &APenguin::Right);
		EnhanceInputCom->BindAction(UpInput, ETriggerEvent::Started, this, &APenguin::Up);


		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Completed, this, &APenguin::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Completed, this, &APenguin::Right);
	

		EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Triggered, this, &APenguin::MouseX);
		EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Triggered, this, &APenguin::MouseY);

		EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Completed, this, &APenguin::MouseX);
		EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Completed, this, &APenguin::MouseY);

		EnhanceInputCom->BindAction(ShootInput, ETriggerEvent::Started, this, &APenguin::Shoot);
		EnhanceInputCom->BindAction(ReloadInput, ETriggerEvent::Started, this, &APenguin::Reload);
		EnhanceInputCom->BindAction(RestartInput, ETriggerEvent::Started, this, &APenguin::Restart);

		EnhanceInputCom->BindAction(SettingsInput, ETriggerEvent::Started, this, &APenguin::ToggleSettings);
	}
}

void APenguin::HitByTarget()
{
	Lives--;
	if (Lives <= 0)
	{
		/*GameOver = true;*/
		return;
		// TODO : Game over
	}
}

void APenguin::MouseX(const FInputActionValue& input)
{
	Yaw = input.Get<float>();
	AddControllerYawInput(Yaw);
}

void APenguin::MouseY(const FInputActionValue& input)
{
	Pitch = input.Get<float>();
	AddControllerPitchInput(Pitch);
}



void APenguin::Forward(const FInputActionValue& input)
{
	XInput = input.Get<float>();
	
	
}

void APenguin::Up(const FInputActionValue& input)
{
	
	InAir = true;
	Jump();
	
	/*FVector Jump;
	
	
	if (Clock > 2)
		Jump = FVector(0, 0, 0);
	else if(Clock < 2)
		Jump = FVector(0, 0, 5);

	SetActorLocation(GetActorLocation() + (Jump*Clock));*/
	
	
}

void APenguin::Right(const FInputActionValue& input)
{
	YInput = input.Get<float>();


}

void APenguin::Shoot(const FInputActionValue& input)
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

void APenguin::Reload(const FInputActionValue& input)
{
	Ammo = MaxAmmo;
}

void APenguin::Jump()
{

	FVector Jump;
	

	
		Jump = FVector(0, 0, 200);

	FVector JumpHeight = (Jump*(Clock/2));
	SetActorLocation(GetActorLocation() + (JumpHeight * Clock));
	if (Clock >= 1)
		InAir = false;

}

void APenguin::Drift()
{
	FVector Drift = FVector(XInput, YInput, 0);
	SetActorLocation(GetActorLocation() + Drift*Clock);
}
