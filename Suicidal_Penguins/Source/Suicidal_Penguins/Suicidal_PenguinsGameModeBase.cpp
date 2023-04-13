// Copyright Epic Games, Inc. All Rights Reserved.


#include "Suicidal_PenguinsGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Start_Stop.h"
#include "Penguin.h"



ASuicidal_PenguinsGameModeBase::ASuicidal_PenguinsGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASuicidal_PenguinsGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void ASuicidal_PenguinsGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASuicidal_PenguinsGameModeBase::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(FString("Save1"), 0)) // Save Name, UserIndex
	{
		USaveGame* save = UGameplayStatics::LoadGameFromSlot(FString("Save1"), 0);
		UStart_Stop* mySave = Cast<UStart_Stop>(save);

		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (character == nullptr) return;

		APenguin* player = Cast<APenguin>(character);
		if (player == nullptr) return;

		mySave->Position = player->GetActorLocation();
		mySave->Rotation = player->GetActorRotation();
		

		UGameplayStatics::SaveGameToSlot(mySave, FString("Save1"), 0);
	}
	else
	{
		USaveGame* save = UGameplayStatics::CreateSaveGameObject(SaveGame_BP);
		UStart_Stop* mySave = Cast<UStart_Stop>(save);

		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (character == nullptr) return;

		APenguin* player = Cast<APenguin>(character);
		if (player == nullptr) return;

		mySave->Position = player->GetActorLocation();
		mySave->Rotation = player->GetActorRotation();
		
		UGameplayStatics::SaveGameToSlot(mySave, FString("Save1"), 0);
	}
}

void ASuicidal_PenguinsGameModeBase::LoadGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(FString("Save1"), 0)) return;

	USaveGame* save = UGameplayStatics::LoadGameFromSlot(FString("Save1"), 0);
	UStart_Stop* mySave = Cast<UStart_Stop>(save);

	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (character == nullptr) return;

	APenguin* player = Cast<APenguin>(character);
	if (player == nullptr) return;

	player->SetActorLocation(mySave->Position);
	player->SetActorRotation(mySave->Rotation);
	
}
