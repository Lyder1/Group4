// EDVARD ANDREASSEN


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
		RootComponent = CollisionComponent;
	}

	if (!ArrowMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ArrowMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ArrowMovementComponent->SetUpdatedComponent(CollisionComponent);
		ArrowMovementComponent->InitialSpeed = 10000.0f;
		ArrowMovementComponent->MaxSpeed = 10000.0f;
		ArrowMovementComponent->bRotationFollowsVelocity = true;
		ArrowMovementComponent->bShouldBounce = false;
		//ArrowMovementComponent->Bounciness = 0.3f;
		ArrowMovementComponent->ProjectileGravityScale = 1.0f;
	}

	if (!ArrowMesh) {
		ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
		ArrowMesh->SetupAttachment(CollisionComponent);
	}

	//lifespan of arrow after being fired
	InitialLifeSpan = 3.0f;

	/*if (!NewArrowMesh) {
		NewArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
		NewArrowMesh->SetupAttachment(ArrowMesh);
	}*/
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

void AArrow::FireInDirection(const FVector& ShootDirection)
{
	ArrowMovementComponent->Velocity = ShootDirection * ArrowMovementComponent->InitialSpeed;
}

