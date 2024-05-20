// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
	CurrentHealth = MaxHealth;

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

	Speed = MaxSpeed;

	//there a multible components in the enemy. the detection area is for finding the player. and when the detection area overlaps with something and stops overlapping it calls these two functions
	DetectionArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnDetectionBegin);
	DetectionArea->OnComponentEndOverlap.AddDynamic(this, &AMyEnemy::OnDetectionEnd);

	//Same thing here the attack area is where the enemy is able to attack the player. so when the player goes into or leaves the attack area it calls these functions
	AttackArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::AttackStart);
	AttackArea->OnComponentEndOverlap.AddDynamic(this, &AMyEnemy::AttackEnd);

	//This is just here so that the player also takes damage from explosive barrels
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
	//gets all actos withing detecionarea
	TArray<AActor*> OverlappingActors;
	DetectionArea->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		// Check if any of overlapped actors is the player		
		AMyArcher* PlayerCharacter = Cast<AMyArcher>(Actor);
		if (PlayerCharacter)
		{
			Scanning = true;
			// Perform a line trace from the enemy to the player to see if there is a wall between them and it should not be able to "see" the player
			FHitResult HitResult;
			LTStartLocation = GetActorLocation() + FVector(0, 0, 50);
			LTEndLocation = PlayerCharacter->GetActorLocation();
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);

			// Perform the line trace
			bool HitWall = GetWorld()->LineTraceSingleByChannel(HitResult, LTStartLocation, LTEndLocation, ECC_Visibility, Params);

			//Starts chasing if the line trace hits the player
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
	//stops chasing
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
	//this function gets called from MyArcher.cpp if the archer hits the enemy
	if(Alive) {
		DetectionArea->SetSphereRadius(2000.0f);
		Detected = true;
		CurrentHealth--;
	}
}

void AMyEnemy::AttackStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if player enters attack area it deals damage to archer by turning "Attacking = true"
	Player = Cast<AMyArcher>(OtherActor);
	if (OtherActor->IsA<AMyArcher>() && Alive) {
		MidSwing = false;
		Attacking = true;

		StopMovement();
	}
}

void AMyEnemy::AttackEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Just gives the archer a headstart if the armor gets to close. starts movement after 1 second of leaving the attack area
	if(Alive){
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::StartMovement, 01.0f, false);
	}
}

void AMyEnemy::ExplosionDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//once again the main reason hitbox component here is so that 
	if (Alive && OtherComp->ComponentHasTag("Exploded")) {
		DetectionArea->SetSphereRadius(2000.0f);
		Detected = true;
		CurrentHealth -= 5;
	}
}

void AMyEnemy::StopMovement()
{	//stops movement for when the armor reaches the player so that it does not continue to run toward player when reaching her
	Speed = 0.0f;
	MovementStopped = true;
}

void AMyEnemy::StartMovement()
{
	//starts movement again after being stopped
	Speed = MaxSpeed;
	Attacking = false;
	MovementStopped = false;
}

void AMyEnemy::Die()
{
	//feel like this function explains itself pretty well
	Destroy();
}


FVector AMyEnemy::GetPlayerLocation(UWorld* World)
{
	//for some reason i could no longer get player location thorugh thefirstcontrooller() thing. so i had to make this gigantic thing to get the player location
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
	//delays the damage amount so that the archer can only lose hp every 1.5 seconds when continuously standing in the attackarea
	MidSwing = false;
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	//here is the movement part, it calculates where it has to go and goes towards the target (player)
	Super::Tick(DeltaTime);
	StartLocation = GetActorLocation();
	PlayerLocation = GetPlayerLocation(GetWorld());
	Direction = PlayerLocation - StartLocation;
	TotalDistance = Direction.Size();

	Direction.Normalize();

	if (Detected && CurrentDistance < TotalDistance && Alive && !MovementStopped) {
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
		CurrentDistance = (NewLocation - StartLocation).Size();

		//line trace to keep the enemy to the ground becuase i decided to be stupid and make my own bad movement component, when i could start out with one implemented if i pushed the right buttons but now i have comitted to this and i will cry if i ever remove it
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
	//restricts the damage the archer can get
	if (Attacking && !MidSwing) {
		MidSwing = true;
		Player->OnHit();
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::MidSwingDelay, 01.5f, false);
	}
	//keeps searching for player if it detects that the player is inside the detection area, but is behind something
	if (Scanning) {
		WallDetectionCheck();
	}

	//handles death logic
	if (CurrentHealth == 0 && Alive) {
		Alive = false;
		DetectionArea->SetSphereRadius(0.0f);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("HP: %d"), CurrentHealth));  // Debug message
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

