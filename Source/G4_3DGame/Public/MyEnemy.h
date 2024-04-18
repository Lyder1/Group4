// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyArcher.h"
#include "TimerManager.h"
#include "MyEnemy.generated.h"


UCLASS()
class G4_3DGAME_API AMyEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyEnemy();

protected:
	FTimerHandle DelayTimerHandle;

	float MaxGroundCheckDistance = 50.0f;
	float TotalDistance;
	float CurrentDistance = 0.0f;
	float HomeTotalDistance;
	float HomeCurrentDistance = 0.0f;
	FVector Direction;
	FVector PlayerLocation;
	FVector StartLocation;
	FVector HomeDirection;
	FVector HomeLocation;
	FVector CurrentLocation;
	FRotator HomeRotation;
	bool Detected = false;
	bool Escaping = false;
	bool EnemyIsHome;
	bool DelayedRotation = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor")
	class USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveActor")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detection")
	class USphereComponent* DetectionArea;

	UFUNCTION()
	void OnDetectionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDetectionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void DetectionEndReaction();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
