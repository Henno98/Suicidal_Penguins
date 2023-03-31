// Fill out your copyright notice in the Description page of Project Settings.


#include "SeaLeopard.h"
#include "Goal.h"
#include "Player_Penguin.h"
#include "Components/BoxComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "Engine/StaticMeshSocket.h"
#include "Bullet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	
	MovementSpeed = 0;
	RotationSpeed = 0.f;
	ShootDelay = 3.f;
	TimeSinceShooting = 3.f;
}

// Called when the game starts or when spawned
void ASeaLeopard::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASeaLeopard::PawnSeen(APawn* SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Seen Pawn"));
}

// Called every frame
void ASeaLeopard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &ASeaLeopard::PawnSeen);

		APlayer_Penguin* Player = Cast<APlayer_Penguin>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
		if (Player)
		{
			FRotator NewRotation{ UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation()) };
			SetActorRotation(NewRotation);
		}
		
		TimeSinceShooting += DeltaTime;
		if (TimeSinceShooting > ShootDelay)
		{
			Shoot();
			TimeSinceShooting = 0.f;
		}
		
	}
	
	//Move
	
	// if (const AActor* Player = pc->GetPawn())
	// {
	// 	const FVector PawnLocation = Player->GetActorLocation();
	// 	FVector VectorPtoT = PawnLocation - NewLocation;
 // 		VectorPtoT.Normalize();
	// 	VectorPtoT *= FVector(1, 1, 0);
	// 	FRotator newrot = (Player - GetActorLocation()).Rotation();
	// 	SetActorLocation(NewLocation + VectorPtoT * MovementSpeed * DeltaTime);
	// }

	//Rotate
	// SetActorRotation(GetActorRotation() + FRotator(0, ->GetActorLocation(), 0));
	
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
	GetWorld()->SpawnActor<AActor>(BP_Bullet,                                        // What to spawn
		GetActorLocation(), GetActorRotation());								// Location & Rotation
}
