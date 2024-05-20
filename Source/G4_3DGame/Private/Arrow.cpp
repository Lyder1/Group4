// EDVARD ANDREASSEN


#include "Arrow.h"
#include "MyEnemy.h"

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision profile name to "Projectile".
	//CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(15.0f);
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnHit);

	// Use this component to drive this projectile's movement.
	ArrowMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ArrowMovementComponent->SetUpdatedComponent(CollisionComponent);
	ArrowMovementComponent->InitialSpeed = 100.0f;
	ArrowMovementComponent->MaxSpeed = 10000.0f;
	ArrowMovementComponent->bRotationFollowsVelocity = true;
	ArrowMovementComponent->bShouldBounce = false;
	//ArrowMovementComponent->Bounciness = 0.3f;
	ArrowMovementComponent->ProjectileGravityScale = 1.0f;

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
	ArrowMesh->SetupAttachment(CollisionComponent);


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
//determines if the arrow hits the player and handles damage
void AArrow::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//checks if the detected components is eiter the arrow, the enemy detection area or the enemy attack area
	if (OtherComp->GetOwner() == this || OtherComp->ComponentHasTag("DetectionArea") || (OtherComp->ComponentHasTag("AttackArea"))) {
		return;
	}
	//checks if the hit component is the Enemy hitbox by looking for the tag "hitbox". it calls Enemy OnHit() function if the component has the right tag and then destroys itself
	if (OtherComp->ComponentHasTag("HitBox")) {
		AMyEnemy* Enemy = Cast<AMyEnemy>(OtherActor);
		Enemy->OnHit();
		Destroy();

	}
	//if the arrow hits anything not specified it destroys itself
	Destroy();
}

void AArrow::FireInDirection(const FVector& ShootDirection, float ChargeRate)
{
	ArrowMovementComponent->Velocity = ShootDirection * ChargeRate;
}

