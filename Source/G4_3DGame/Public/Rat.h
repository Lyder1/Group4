// EDVARD ANDREASSEN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Rat.generated.h"

struct FInputActionValue;

UCLASS()
class G4_3DGAME_API ARat : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ARat();

	
	// COMPONENTS


	// RAt Spring Arm 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class USpringArmComponent* RatSpringArm;

	// Rat Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UCameraComponent* RatCamera;

	//Rat Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* RatMesh;


	// INPUT ACTIONS AND IMC


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* JumpAction;


	// FUNCTIONS


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
