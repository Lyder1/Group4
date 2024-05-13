// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableWall.generated.h"

UCLASS()
class G4_3DGAME_API ABreakableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RootScene;

	UPROPERTY(EditAnyWhere, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Collision")
	class UCapsuleComponent* CollisionComponent;

	UFUNCTION()
	void Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
