// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "TimerManager.h"
#include "Arrow.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	DetectionArea = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionArea"));
	DetectionArea->SetSphereRadius(900.0f);
	DetectionArea->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(RootComponent);

	DetectionArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnDetectionBegin);
	DetectionArea->OnComponentEndOverlap.AddDynamic(this, &AMyEnemy::OnDetectionEnd);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



void AMyEnemy::OnDetectionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(DelayTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
	}
	if(OtherActor->IsA<AMyArcher>()){
		DetectionArea->SetSphereRadius(1750.0f);
		Detected = true;
		DelayedRotation = false;
	}


}


void AMyEnemy::OnDetectionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::DetectionEndReaction, 10.0f, false);
}

void AMyEnemy::DetectionEndReaction()
{
	DetectionArea->SetSphereRadius(900.0f);
	Detected = false;
	EnemyIsHome = false;
}



// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	HomeLocation = GetActorLocation();
	HomeRotation = GetActorRotation();
	
}

void AMyEnemy::OnHit()
{
	HP--;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT(""), HP));
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StartLocation = GetActorLocation();
	PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	Direction = PlayerLocation - StartLocation;
	TotalDistance = Direction.Size();

	HomeDirection = HomeLocation - StartLocation;
	HomeTotalDistance = HomeDirection.Size();

	Direction.Normalize();
	HomeDirection.Normalize();

	if (Detected && CurrentDistance < TotalDistance) {
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
		CurrentDistance = (NewLocation - StartLocation).Size();

		//Line trace to check for ground bellow
		FVector DownVector = FVector(0.0f, 0.0f, -5.0f);
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		FVector EndLocation = NewLocation + DownVector * MaxGroundCheckDistance;

		if (GetWorld()->LineTraceSingleByChannel(Hit, NewLocation, EndLocation, ECC_WorldStatic, Params)){
			NewLocation = Hit.ImpactPoint;
		}
		SetActorLocation(NewLocation);

		FRotator TargetRotation = (PlayerLocation - NewLocation).Rotation() - FRotator(0.0f, 90.0f, 0.0f);
		SetActorRotation(FRotator(0.0f, TargetRotation.Yaw, 0.0f));
	}
	if (!Detected && !EnemyIsHome && HomeCurrentDistance < HomeTotalDistance) {

		FVector NewLocation = GetActorLocation() + HomeDirection * Speed * DeltaTime;
		HomeCurrentDistance = (NewLocation - StartLocation).Size();

		//Line trace to check for ground bellow
		FVector DownVector = FVector(0.0f, 0.0f, -5.0f);
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		FVector EndLocation = NewLocation + DownVector * MaxGroundCheckDistance;

		if (GetWorld()->LineTraceSingleByChannel(Hit, NewLocation, EndLocation, ECC_WorldStatic, Params)) {
			NewLocation = Hit.ImpactPoint;
		}
		SetActorLocation(NewLocation);
		FRotator TargetRotation = (HomeLocation - NewLocation).Rotation() - FRotator(0.0f, 90.0f, 0.0f);
		SetActorRotation(FRotator(0.0f, TargetRotation.Yaw, 0.0f));
		
		CurrentLocation = GetActorLocation();
		DelayedRotation = true;
	}else if (DelayedRotation) {
		SetActorRotation(FRotator(0.0f, HomeRotation.Yaw, 0.0f));
		DelayedRotation = false;
	}
	if (HP <= 0) {
		Destroy();
	}
}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

