// Fill out your copyright notice in the Description page of Project Settings.


#include "MyArcher.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyArcher::AMyArcher()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ArcherSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	ArcherSpringArm->SetupAttachment(GetMesh());

	ArcherCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	ArcherCamera->AttachToComponent(ArcherSpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	ArcherSpringArm->bUsePawnControlRotation = true;
	ArcherSpringArm->bEnableCameraLag = true;
	ArcherSpringArm->TargetArmLength = 300.0f;
	//ArcherSpringArm->TargetOffset = 

}

// Called when the game starts or when spawned
void AMyArcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

