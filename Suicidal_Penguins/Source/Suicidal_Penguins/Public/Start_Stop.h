// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Start_Stop.generated.h"

/**
 * 
 */
UCLASS()
class SUICIDAL_PENGUINS_API UStart_Stop : public USaveGame
{
	GENERATED_BODY()
public:

	UStart_Stop();

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
		FVector Position;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
		FRotator Rotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
		int Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Game")
		float Experience;
	
};
