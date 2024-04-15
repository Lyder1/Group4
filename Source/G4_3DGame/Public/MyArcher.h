// EDVARD ANDREASSEN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Arrow.h"
#include "MyArcher.generated.h"

struct FInputActionValue;

UCLASS()
class G4_3DGAME_API AMyArcher : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyArcher();


	// COMPONENTS


	// Archer spring arm, to allow for third person perspective
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class USpringArmComponent* ArcherSpringArm;

	// Archer Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UCameraComponent* ArcherCamera;

	//Archer Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* ArcherMesh;

	// Origin offset for where arrow will spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector ArrowOrigin;

	// Which class projectile to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AArrow> ProjectileClass;


	// INPUT ACTIONS AND IMC


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* FireAction;


	// FUNCTIONS


	void Move(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

	UFUNCTION()
	void FireArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
