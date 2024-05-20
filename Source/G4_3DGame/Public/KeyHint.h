// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "Components/SphereComponent.h"
#include "KeyHint.generated.h"

UCLASS()
class G4_3DGAME_API AKeyHint : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyHint();


	// COMPONENTS


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* HintMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* CollisionSphere;


	// VARIABLES

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool IsPressed = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void InteractWithThis() override;
};
