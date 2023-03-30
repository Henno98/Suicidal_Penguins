// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Target.generated.h"

class UBoxComponent;

UCLASS()
class SUICIDAL_PENGUINS_API ATarget : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATarget();

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

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void DestroyTarget();

	//Variables
	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float RotationSpeed;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float XKillPosition;
};
