// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyArcher.h"
#include "MyEnemy.generated.h"


UCLASS()
class G4_3DGAME_API AMyEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyEnemy();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor")
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BLueprintReadOnly, Category = "MoveActor")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveActor")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detection")
	class USphereComponent* DetectionArea;

	UFUNCTION()
	void OnDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void HandleDetection(AActor* DetectedActor);


	FVector Direction;

	float TotalDistance;
	float CurrentDistance;
	FVector StartLocation;

	bool Detected = false;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
