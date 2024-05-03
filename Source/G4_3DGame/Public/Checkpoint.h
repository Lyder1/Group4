// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Checkpoint.generated.h"

UCLASS()
class G4_3DGAME_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();


	// COMPONENTS


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* CollisionMesh;


	// FUNCTIONS


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
