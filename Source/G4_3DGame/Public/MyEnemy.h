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
	float RevertSpeed;
	FVector Direction;
	FVector PlayerLocation;
	FVector LTStartLocation;
	FVector LTEndLocation;
	FVector StartLocation;
	FVector HomeDirection;
	FVector HomeLocation;
	FVector CurrentLocation;
	FRotator HomeRotation;
	FVector RevertDirection;
	FVector RevertPlayerLocation;
	FVector RevertStartLocation;
	bool Scanning = false;
	bool Escaping = false;
	bool EnemyIsHome;
	bool DelayedRotation = false;
	bool Alive = true;
	bool MovementStopped = false;
	bool IsChasing = false;
	bool MidSwing = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor")
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int HP = 5;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	AMyArcher* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detection")
	class USphereComponent* DetectionArea;

	UPROPERTY(BlueprintReadWrite, Category = "Status")
	bool Detected = false;

	UPROPERTY(BlueprintReadWrite, Category = "Status");
	bool Attacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	class USphereComponent* AttackArea;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "HitBox")
	class UCapsuleComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveActor")
	float Speed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Animation")
	bool OnGoingAttackAnim = false;


	UFUNCTION()
	void OnHit();

	UFUNCTION()
	void OnDetectionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void WallDetectionCheck();

	UFUNCTION()
	void OnDetectionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void AttackStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void AttackEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ExplosionDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	//UFUNCTION()
//	void Attack();

	void StopMovement();
	void StartMovement();
	void Die();
	void AnimEnd();
	FVector GetPlayerLocation(UWorld* World);
	void MidSwingDelay();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
