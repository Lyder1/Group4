// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	DetectionArea = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionArea"));
	DetectionArea->InitSphereRadius(500.0f);
	DetectionArea->SetupAttachment(RootComponent);

	//Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//Mesh->SetupAttachment(RootComponent);

	DetectionArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnDetection);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyEnemy::OnDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Detected = true;
}





// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("YourVariable: %d"), Detected));

	StartLocation = GetActorLocation();
	Direction = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation() - StartLocation;
	TotalDistance = Direction.Size();

	Direction = Direction.GetSafeNormal();
	CurrentDistance = 0.0f;

	if (Detected) {
		if (CurrentDistance < TotalDistance) {
			FVector Location = GetActorLocation();
			Location += Direction * Speed * DeltaTime;
			SetActorLocation(Location);
			CurrentDistance = (Location - StartLocation).Size();

			FRotator NewRotation = Direction.Rotation();
			SetActorRotation(NewRotation - FRotator(0.0f, 90.0f, 0.0f));

		}
	}
}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

