// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorKey.h"

// Sets default values
ADoorKey::ADoorKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Key Collision Sphere"));
	RootComponent = CollisionSphere;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Static Mesh"));
	KeyMesh->SetupAttachment(CollisionSphere);

}



// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorKey::InteractWithThis() 
{
	IsHeld = true;
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Picked up key"));
}

