// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"
#include "SeaLeopard.h"
#include "Player_Penguin.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitSphereRadius(20.f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	MovementSpeed = 2000.f;
	TimeLived = 0.f;
	LifeSpan = 10.f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);


	TimeLived += DeltaTime;
	if (TimeLived > LifeSpan)
	{
		DestroyBullet();
	}
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APlayer_Penguin>())
	{
		//Destroy Target
		Cast<AEnemy>(OtherActor)->DestroyTarget();

		//Destroys bullet
		DestroyBullet();
	}
	// else if (OtherActor->IsA<ASeaLeopard>())
	// {
	// 	//Destroy Target
	// 	Cast<AEnemy>(OtherActor)->DestroyTarget();
	//
	// 	//Destroys bullet
	// 	DestroyBullet();
	// }
	// else if (OtherActor->IsA<APlayer_Penguin>())
	// {
	// 	//Destroys bullet
	// 	DestroyBullet();
	// }
	
}

void ABullet::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}