// Fill out your copyright notice in the Description page of Project Settings.


#include "SeaLeopard.h"
#include "Goal.h"
#include "Player_Penguin.h"
#include "Components/BoxComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Bullet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASeaLeopard::ASeaLeopard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(100, 100, 100));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASeaLeopard::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, 40));

	// SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	// SkeletalMesh->SetupAttachment(GetRootComponent());
	// SkeletalMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	// SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, 40));
	
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 7000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);
	
	MovementSpeed = 350;
	RotationSpeed = 0.f;
	// Ammo = 10;
	// MaxAmmo = 10;
}

// Called when the game starts or when spawned
void ASeaLeopard::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASeaLeopard::PawnSeen(APawn* SeenPawn)
{
	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &ASeaLeopard::PawnSeen);
	}
}

// Called every frame
void ASeaLeopard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Shoot
	// if ()
	// {
	// 	
	// }
	Shoot();
	
	//Move
	// FVector NewLocation = GetActorLocation();

	// if (const AGoal* Goal = )
	// 	if (const APawn* Pawnpc = pc->GetPawn())
	// 	{
	// 		const FVector PawnLocation = Pawnpc->GetActorLocation();
	// 		FVector VectorPtoT = PawnLocation - NewLocation;
	// 		VectorPtoT.Normalize();
	// 		VectorPtoT *= FVector(1, 1, 0);
	// 		/*FRotator newrot = (Pawnpc - GetActorLocation()).Rotation();*/
	// 		SetActorLocation(NewLocation + VectorPtoT * MovementSpeed * DeltaTime);
	// 	}

	//Rotate
	/*SetActorRotation(GetActorRotation() + FRotator(0, Pawnpc->GetActorLocation(), 0));*/

	//kill
	// if (GetActorLocation().X < XKillPosition)
	// {
	// 	DestroyTarget();
	// }
}

void ASeaLeopard::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APlayer_Penguin>())
	{
		Cast<APlayer_Penguin>(OtherActor)->HitByTarget();

		DestroyTarget();
	}
}

void ASeaLeopard::DestroyTarget()
{
	// SetActorHiddenInGame(true);
	// SetActorEnableCollision(false);
	// this->Destroy();
}

// Shoot towards the player
void ASeaLeopard::Shoot()
{
	GetWorld()->SpawnActor<AActor>(BP_Bullet,				// What to spawn
				 GetActorLocation(), GetActorRotation());	// Location & Rotation
	// if (Ammo > 0)
	// {
	// 	Ammo--;
	// 	
	// 	GetWorld()->SpawnActor<AActor>(BP_Bullet,                                        // What to spawn
	// 			 GetActorLocation(), GetActorRotation());								// Location & Rotation
	// }
	// else
	// {
	// 	ReloadDelay = 5;
	// 	if (ReloadDelay == 0)
	// 	{
	// 		Ammo = MaxAmmo;
	// 	}
	// 	ReloadDelay--;
	// }
}

void ASeaLeopard::Delay(float Time)
{
	// ReloadDelay = Time * 100000000;
	// if (ReloadDelay == 0)
	// {
	// 	Ammo = MaxAmmo;
	// }
	// ReloadDelay--;
}