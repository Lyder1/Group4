// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Explosive_Barrel.generated.h"

UCLASS()
class G4_3DGAME_API AExplosive_Barrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosive_Barrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DelayTimerHandle;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "HitBox")
	class USphereComponent* HitBox;

	UPROPERTY(EditAnywhere)
	float ExplosionDamage;

	UPROPERTY(EditAnywhere)
	float ExplosionRadius;

	

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* ExplosionSound;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SoundRemoved();
	void Explode();

	bool Exploded;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
