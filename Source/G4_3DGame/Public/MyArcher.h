// EDVARD ANDREASSEN

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Arrow.h"
#include "InteractionInterface.h"
#include "TimerManager.h"
#include "Engine/World.h"

#include "MyArcher.generated.h"

struct FInputActionValue;

UCLASS()
class G4_3DGAME_API AMyArcher : public ACharacter, public IInteractionInterface
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* InteractBox;

	// Origin offset for where arrow will spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector ArrowOrigin;

	// Which class projectile to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AArrow> ProjectileClass;


	// VARIABLES


	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* MoveAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float PlayerHealth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float MaxHealth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	int Ammo = 10;

	class USaveGame* LoadObj;

	class UMySaveGame* saveObj;

	IInteractionInterface* Interface = nullptr;

	FTimerHandle DelayTimerHandle;

	bool Damaged = false;
	bool IsMoving = false;
	bool AttackPrimed = true;
	bool Dead = false;


	// INPUT ACTIONS AND IMC


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsCharging = false;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* ChargeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LoadAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* InteractAction;


	// FUNCTIONS


	void Move(const FInputActionValue& Value);

	void OnHit();

	void LookAround(const FInputActionValue& Value);

	void InputLoad(const FInputActionValue& Value);

	void SaveGame();

	void Interact();

	UFUNCTION()
	void FireArrow();

	UFUNCTION()
	void ChargeArrow();

	UFUNCTION()
	void InteractOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherbodyIndex);

	void InputInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
