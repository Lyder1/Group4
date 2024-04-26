// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive_Barrel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExplosive_Barrel::AExplosive_Barrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	RootComponent = Mesh;

	HitBox = CreateDefaultSubobject<USphereComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
	//HitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//HitBox->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	//HitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//HitBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Health = 100.0f;
	ExplosionDamage = 50.0f;
	ExplosionRadius = 300.0f;
	Exploded = false;

	HitBox->OnComponentHit.AddDynamic(this, &AExplosive_Barrel::OnHit);
}

// Called when the game starts or when spawned
void AExplosive_Barrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosive_Barrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!Exploded && (OtherComp->ComponentHasTag("DetectionArea")))
	{
		Explode();
	}
}

void AExplosive_Barrel::Explode()
{
	/*if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr, IgnoreActors, this);

	Exploded = true;

	Destroy();*/
}

// Called every frame
void AExplosive_Barrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

