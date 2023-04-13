// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class UBoxComponent;
class ABullet;
class UPawnSensingComponent;

UCLASS()
class SUICIDAL_PENGUINS_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PawnSeen(APawn* SeenPawn);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Collider {
		nullptr
	};

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// 	USkeletalMeshComponent* SkeletalMesh;

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
	
	UFUNCTION()
		void Delay(float Time);

	//Variables
	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float RotationSpeed;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	// int Ammo;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	// int MaxAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int ReloadDelay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<ABullet> BP_Bullet;

private:
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;
};