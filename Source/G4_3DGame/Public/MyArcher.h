// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyArcher.generated.h"

struct FInputActionValue;

UCLASS()
class G4_3DGAME_API AMyArcher : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyArcher();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class USpringArmComponent* ArcherSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UCameraComponent* ArcherCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* ArcherMesh;

	// Input Actions and IMC

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* JumpAction;

	void Move(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
