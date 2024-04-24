// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "MyEnemy.h"

// Sets default values
AArrow::AArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	
	// Use this component to drive this projectile's movement.
	ArrowMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ArrowMovementComponent->SetUpdatedComponent(RootComponent);
	ArrowMovementComponent->InitialSpeed = 7000.0f;
	ArrowMovementComponent->MaxSpeed = 7000.0f;
	ArrowMovementComponent->bRotationFollowsVelocity = true;
	ArrowMovementComponent->bShouldBounce = false;
	//ArrowMovementComponent->Bounciness = 0.3f;
	ArrowMovementComponent->ProjectileGravityScale = 1.0f;

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
	ArrowMesh->SetupAttachment(RootComponent);
	
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision profile name to "Projectile".
	//CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(15.0f);
	// Set the root component to be the collision component.
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnHit);
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OnHit function called"));
	if (OtherComp->GetOwner() == this || OtherComp->ComponentHasTag("DetectionArea")) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Arrow Ignored"));
		return;
	}
	if (OtherComp->ComponentHasTag("HitBox")) {
		AMyEnemy* Enemy = Cast<AMyEnemy>(OtherActor);
		Enemy->OnHit();
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enemy Hit"));

	}
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Arrow Destroyed"));
}

void AArrow::FireInDirection(const FVector& ShootDirection)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Arrow Fired"));
	ArrowMovementComponent->Velocity = ShootDirection * ArrowMovementComponent->InitialSpeed;
}

