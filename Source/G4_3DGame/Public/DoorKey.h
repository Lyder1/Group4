// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "InteractionInterface.h"
#include "DoorKey.generated.h"

UCLASS()
class G4_3DGAME_API ADoorKey : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorKey();


	// COMPONENTS


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* CollisionSphere;


	// VARIABLES


	bool IsHeld = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	int	KeyIndex;


	// FUNCTIONS


	UFUNCTION()
	int GetKeyIndex() { return KeyIndex; } 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithThis() override;

};
