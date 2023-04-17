// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SeaLeopard.generated.h"

class UBoxComponent;
class ABullet;
class UPawnSensingComponent;

UCLASS()
class SUICIDAL_PENGUINS_API ASeaLeopard : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASeaLeopard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Collider {
		nullptr
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyTarget();

	UFUNCTION()
	void Shoot();

	//Variables
	// UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	// float MovementSpeed;
	//
	// UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	// float RotationSpeed;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float ShootDelay;
	
	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float TimeSinceShooting;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	bool CanShoot;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	bool StopMoving;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float StopDuration;
	
	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float StopInterval;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float RotationSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<ABullet> BP_Bullet;

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensing;
};

