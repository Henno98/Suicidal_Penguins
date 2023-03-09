// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Player_Penguin.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"
#include "Target.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(100, 100, 100));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
	SkeletalMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, 40));

	MovementSpeed = 350;
	RotationSpeed = 0.f;
	XKillPosition = -200.f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	/*RotationSpeed = FMath::RandRange(0.5f, 1.5f);*/
	MovementSpeed += FMath::RandRange(0, 250);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move
	FVector NewLocation = GetActorLocation();

	if (const APlayerController* pc = GetWorld()->GetFirstPlayerController())
		if (const APawn* Pawnpc = pc->GetPawn())
		{
			const FVector PawnLocation = Pawnpc->GetActorLocation();
			FVector VectorPtoT = PawnLocation - NewLocation;
			VectorPtoT.Normalize();
			VectorPtoT *= FVector(1, 1, 0);
			/*FRotator newrot = (Pawnpc - GetActorLocation()).Rotation();*/
			SetActorLocation(NewLocation + VectorPtoT * MovementSpeed * DeltaTime);
		}

	//Rotate
	/*SetActorRotation(GetActorRotation() + FRotator(0, Pawnpc->GetActorLocation(), 0));*/

	//kill
	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}
}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APlayer_Penguin>())
	{
		Cast<APlayer_Penguin>(OtherActor)->HitByTarget();

		DestroyTarget();
	}
}

void AEnemy::DestroyTarget()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}