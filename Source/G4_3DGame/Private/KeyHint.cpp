// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyHint.h"

// Sets default values
AKeyHint::AKeyHint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hint Collision Sphere"));
	RootComponent = CollisionSphere;

	HintMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hint Static Mesh"));
	HintMesh->SetupAttachment(CollisionSphere);

}



// Called when the game starts or when spawned
void AKeyHint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyHint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyHint::InteractWithThis()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("No Ammo"));
	IsPressed = true;
}

