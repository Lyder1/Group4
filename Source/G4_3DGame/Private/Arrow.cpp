// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision profile name to "Projectile".
		//CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		CollisionComponent->SetupAttachment(ArrowMesh);
	}

	if (!ArrowMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ArrowMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ArrowMovementComponent->SetUpdatedComponent(RootComponent);
		ArrowMovementComponent->InitialSpeed = 1000.0f;
		ArrowMovementComponent->MaxSpeed = 1000.0f;
		ArrowMovementComponent->bRotationFollowsVelocity = true;
		ArrowMovementComponent->bShouldBounce = false;
		//ArrowMovementComponent->Bounciness = 0.3f;
		ArrowMovementComponent->ProjectileGravityScale = 1.0f;
	}

	if (!ArrowMesh) {
		ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
		ArrowMesh->SetupAttachment(RootComponent);
	}

	/*if (!NewArrowMesh) {
		NewArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
		NewArrowMesh->SetupAttachment(ArrowMesh);
	}*/
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnHit);
	FCollisionQueryParams Params;
	Params.AddIgnoredComponent(ArrowMesh);
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArrow::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this) {
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Arrow Destroyed"));
	}
}

void AArrow::FireInDirection(const FVector& ShootDirection)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Arrow Fired"));
	ArrowMovementComponent->Velocity = ShootDirection * ArrowMovementComponent->InitialSpeed;
}

