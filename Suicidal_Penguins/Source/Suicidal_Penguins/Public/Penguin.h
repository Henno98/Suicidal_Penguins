// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Penguin.generated.h"

class ABullet;
struct FInputActionValue;


UCLASS()
class SUICIDAL_PENGUINS_API APenguin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APenguin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TSubclassOf<ABullet> BP_Bullet;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool CanRestart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool GameOver;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool InAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool RightVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		bool LeftVector;


	/** Public Function */
	void HitByTarget();

	/** Private Variables */
private:
	
	float XInput;
	float YInput;
	float Yaw;
	float Pitch;
	float Clock;

	FVector Velocity;
	FVector Acceleration;
	FVector NaturalBrake;
	FVector RightSlide;

	

	void MouseX(const FInputActionValue& input);
	void MouseY(const FInputActionValue& input);


private:
	/** Private Functions */
	

	void Forward(const FInputActionValue& input);
	void Up(const FInputActionValue& input);
	void Right(const FInputActionValue& input);

	void Shoot(const FInputActionValue& input);
	void Reload(const FInputActionValue& input);

	void Jump();
	void Drift();
public:
	//Input
	UFUNCTION(BlueprintImplementableEvent)
		void ToggleSettings();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* ForwardInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* UpInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* RightInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* ShootInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* ReloadInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* MouseXInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* MouseYInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* RestartInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* DriftInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* SettingsInput;

};
