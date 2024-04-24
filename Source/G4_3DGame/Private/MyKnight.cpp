// Fill out your copyright notice in the Description page of Project Settings.


#include "MyKnight.h"

// Sets default values
AMyKnight::AMyKnight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AMyKnight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


