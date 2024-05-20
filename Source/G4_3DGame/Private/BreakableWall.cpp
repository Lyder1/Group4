// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableWall.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABreakableWall::ABreakableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);


	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	CollisionComponent->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABreakableWall::Explode);

}

// Called when the game starts or when spawned
void ABreakableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableWall::Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("Exploded")) {
		Destroy();
	}
}



// Called every frame
void ABreakableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

