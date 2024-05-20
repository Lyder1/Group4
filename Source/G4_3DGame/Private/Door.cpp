// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Collision Component"));
	RootComponent = CollisionBox;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh Component"));
	DoorMesh->SetupAttachment(CollisionBox);

}


// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::InteractWithThis()
{
	if (LinkedKey && LinkedKey->CheckIfHeld()) {
		LinkedKey->IsHeld = true;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Door unlocked"));
		if (IsOpened) {
			AddActorLocalOffset(MoveCloseDoor, false, 0, ETeleportType::None);
			AddActorLocalRotation(CloseDoor, false, 0, ETeleportType::None);
			
			IsOpened = false;
		}
		else {
			AddActorLocalRotation(OpenDoor, false, 0, ETeleportType::None);
			AddActorLocalOffset(MoveOpenDoor, false, 0, ETeleportType::None);
			
			IsOpened = true;
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Door is locked"));
	}
	
	
}

