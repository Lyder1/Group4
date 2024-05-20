// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyEnemy::AMyEnemy()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	DetectionArea = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionArea"));
	DetectionArea->SetSphereRadius(900.0f);
	DetectionArea->SetupAttachment(RootComponent);

	AttackArea = CreateDefaultSubobject<USphereComponent>(TEXT("AttackArea"));
	AttackArea->SetSphereRadius(104.0f);
	AttackArea->SetupAttachment(RootComponent);

	HitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(RootComponent);

	Speed = 550.0f;

	DetectionArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnDetectionBegin);
	DetectionArea->OnComponentEndOverlap.AddDynamic(this, &AMyEnemy::OnDetectionEnd);

	AttackArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::AttackStart);
	AttackArea->OnComponentEndOverlap.AddDynamic(this, &AMyEnemy::AttackEnd);

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::ExplosionDamage);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



void AMyEnemy::OnDetectionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	WallDetectionCheck();
}

void AMyEnemy::WallDetectionCheck()
{
	// Check if there are any potential targets within the detection radius (sphere collision)
	TArray<AActor*> OverlappingActors;
	DetectionArea->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		// Check if the overlapped actor is the player		
		AMyArcher* PlayerCharacter = Cast<AMyArcher>(Actor);
		if (PlayerCharacter)
		{
			Scanning = true;
			// Perform a line trace from the enemy to the player
			FHitResult HitResult;
			LTStartLocation = GetActorLocation() + FVector(0, 0, 50);
			LTEndLocation = PlayerCharacter->GetActorLocation();
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);

			// Perform the line trace
			bool HitWall = GetWorld()->LineTraceSingleByChannel(HitResult, LTStartLocation, LTEndLocation, ECC_Visibility, Params);

			if (HitResult.GetActor() == PlayerCharacter) {
				if (Alive) {
					DetectionArea->SetSphereRadius(1750.0f);
					Detected = true;
					Scanning = false;
				}
				else {
					return;
				}
			}
		}
	}
}


void AMyEnemy::OnDetectionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Alive && OtherActor->IsA<AMyArcher>()){
		DetectionArea->SetSphereRadius(900.0f);
		Detected = false;
		Scanning = false;
	}
}





// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyEnemy::OnHit()
{
	if(Alive) {
		DetectionArea->SetSphereRadius(2000.0f);
		Detected = true;
		HP--;
	}
}

void AMyEnemy::AttackStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AMyArcher>(OtherActor);
	if (OtherActor->IsA<AMyArcher>() && Alive) {
		MidSwing = false;
		Attacking = true;
		OnGoingAttackAnim = true;

		StopMovement();
	}
}

void AMyEnemy::AttackEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Alive){
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::StartMovement, 01.0f, false);
	}
}

void AMyEnemy::ExplosionDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Alive && OtherComp->ComponentHasTag("Exploded")) {
		DetectionArea->SetSphereRadius(2000.0f);
		Detected = true;
		HP -= 5;
	}
}

void AMyEnemy::StopMovement()
{	
	Speed = 0.0f;
	MovementStopped = true;
}

void AMyEnemy::StartMovement()
{
	Speed = 550.0f;
	Attacking = false;
	MovementStopped = false;
}

void AMyEnemy::Die()
{
	Destroy();
}

void AMyEnemy::AnimEnd()
{
	OnGoingAttackAnim = false;
}

FVector AMyEnemy::GetPlayerLocation(UWorld* World)
{
	if (!World) {
		return FVector::ZeroVector;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (PlayerController) {
		AMyArcher* PlayerCharacter = Cast<AMyArcher>(PlayerController->GetPawn());
		if (PlayerCharacter) {
			PlayerLocation = PlayerCharacter->GetActorLocation();
			return PlayerLocation; 
		}
	}
	return FVector::ZeroVector;

}

void AMyEnemy::MidSwingDelay()
{
	MidSwing = false;
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	StartLocation = GetActorLocation();
	Direction = PlayerLocation - StartLocation;
	PlayerLocation = GetPlayerLocation(GetWorld());
	TotalDistance = Direction.Size();

	HomeDirection = HomeLocation - StartLocation;
	HomeTotalDistance = HomeDirection.Size();

	Direction.Normalize();
	HomeDirection.Normalize();

	if (Detected && CurrentDistance < TotalDistance && Alive && !MovementStopped) {
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
		CurrentDistance = (NewLocation - StartLocation).Size();

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

		FRotator TargetRotation = (PlayerLocation - NewLocation).Rotation() - FRotator(0.0f, 90.0f, 0.0f);
		SetActorRotation(FRotator(0.0f, TargetRotation.Yaw, 0.0f));
	}

	if (Attacking && !MidSwing) {
		MidSwing = true;
		Player->OnHit();
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::MidSwingDelay, 01.5f, false);
	}

	if (Scanning) {
		WallDetectionCheck();
	}

	if (HP == 0 && Alive) {
		Alive = false;
		DetectionArea->SetSphereRadius(0.0f);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("HP: %d"), HP));  // Debug message
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Alive status: %d"), Alive));  // Debug message
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::Die, 05.0f, false);
	}
}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

