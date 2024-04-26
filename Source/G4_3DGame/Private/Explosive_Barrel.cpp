// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive_Barrel.h"

// Sets default values
AExplosive_Barrel::AExplosive_Barrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExplosive_Barrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosive_Barrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

