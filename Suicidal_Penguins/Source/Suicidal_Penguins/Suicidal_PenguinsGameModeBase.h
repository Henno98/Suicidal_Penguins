// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Suicidal_PenguinsGameModeBase.generated.h"

/**
 * 
 */

class UStart_Stop;

UCLASS()

class SUICIDAL_PENGUINS_API ASuicidal_PenguinsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ASuicidal_PenguinsGameModeBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveGame")
		TSubclassOf<UStart_Stop> SaveGame_BP;

public:
	UFUNCTION(BlueprintCallable)
		void SaveGame();

	UFUNCTION(BlueprintCallable)
		void LoadGame();
	
};
