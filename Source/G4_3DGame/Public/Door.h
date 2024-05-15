// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "InteractionInterface.h"
#include "DoorKey.h"
#include "Door.generated.h"

UCLASS()
class G4_3DGAME_API ADoor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();


	// COMPONENTS


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* CollisionBox;


	// VARIABLES


	bool IsOpened = false;

	FQuat CloseDoor = FQuat(FRotator(0, 90.0f, 0));

	FQuat OpenDoor = FQuat(FRotator(0, -90.0f, 0));

	FVector MoveOpenDoor = FVector(-50.0f, 50.0f, 0);

	FVector MoveCloseDoor = FVector(50.0f, -50.0f, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	int DoorIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door | key")
	ADoorKey* LinkedKey;


	// FUNCTIONS

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithThis() override;
};
