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

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AExplosive_Barrel::OnHit);
}

// Called when the game starts or when spawned
void AExplosive_Barrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosive_Barrel::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Exploded && (OtherComp->ComponentHasTag("Arrow")))
	{
		Explode();
	}
}

void AExplosive_Barrel::SoundRemoved()
{
	Destroy();
}

void AExplosive_Barrel::Explode()
{	
	if(ExplosionEffect){
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		ExplosionSound->Play();
	}

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr, IgnoreActors, this);

	Exploded = true;

	Mesh->DestroyComponent();
	HitBox->DestroyComponent();
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AExplosive_Barrel::SoundRemoved, 10.0f, false);
}

// Called every frame
void AExplosive_Barrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

