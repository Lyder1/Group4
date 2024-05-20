// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Explosive_Barrel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExplosive_Barrel::AExplosive_Barrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	Mesh->SetupAttachment(RootComponent);

	HitBox = CreateDefaultSubobject<USphereComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	ExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplosionSound"));
	ExplosionSound->SetupAttachment(RootComponent);
	ExplosionSound->bAutoActivate = false;

	ExplosionDamage = 50.0f;
	ExplosionRadius = 300.0f;
	Exploded = false;

	//calls on hit function if there is a collsion overlap
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AExplosive_Barrel::OnHit);
}

// Called when the game starts or when spawned
void AExplosive_Barrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosive_Barrel::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//it checks if the overlapping compoent has the tag "arrow" and if it does, it calls the explode function
	if (!Exploded && (OtherComp->ComponentHasTag("Arrow")))
	{
		Explode();
	}
}

//fully destroys the rest of itself after explosion
void AExplosive_Barrel::SoundRemoved()
{
	Destroy();
}

void AExplosive_Barrel::Explode()
{	//triggers the eXplosion effect, explosion sound effect, inreases its collsion radius to work as the explosion radius and gives itself the tag "Explode" so that other objects can react
	if(ExplosionEffect){
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		ExplosionSound->Play();
		HitBox->ComponentTags.Add("Exploded");
		HitBox->SetSphereRadius(300.0f);

	}

	//with exploded turned true the explode function cannot be called again, destroys the mesh, and triggers a countdown to call the SoundRemoved() that destroys the rest of the actor
	Exploded = true;

	Mesh->DestroyComponent();
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AExplosive_Barrel::SoundRemoved, 5.0f, false);
}

// Called every frame
void AExplosive_Barrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

