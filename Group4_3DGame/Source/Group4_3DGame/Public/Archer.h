// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Archer.generated.h"

class UCameraComponent;
class UInputMappingContext;
struct FInputActionValue;
class UInputComponent;
class UInputAction;

UCLASS()
class GROUP4_3DGAME_API AArcher : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArcher();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	 * Components
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* ArcherCameraComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* ArcherMesh;

	/*
	 * Input Mapping Context and Actions
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;


	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void LookAround(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
