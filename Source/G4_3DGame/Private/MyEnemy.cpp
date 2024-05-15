// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Arrow.h"	

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

	DetectionArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnDetectionBegin);
	DetectionArea->OnComponentEndOverlap.AddDynamic(this, &AMyEnemy::OnDetectionEnd);

	AttackArea->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::AttackStart);
	AttackArea->OnComponentEndOverlap.AddDynamic(this, &AMyEnemy::AttackEnd);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



void AMyEnemy::OnDetectionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
				//if (GetWorld()->GetTimerManager().IsTimerActive(DelayTimerHandle) && Alive)
				//{
				//	GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
				//}
				if (Alive) {
					DetectionArea->SetSphereRadius(1750.0f);
					Detected = true;
					DelayedRotation = false;
				}
				else {
					return;
				}
			}
		}
	}
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
				//if (GetWorld()->GetTimerManager().IsTimerActive(DelayTimerHandle) && Alive)
				//{
				//	GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
				//}
				if (Alive) {
					DetectionArea->SetSphereRadius(1750.0f);
					Detected = true;
					DelayedRotation = false;
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
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::DetectionEndReaction, 10.0f, false);
	}
}

void AMyEnemy::DetectionEndReaction()
{
		DetectionArea->SetSphereRadius(900.0f);
		Detected = false;
		EnemyIsHome = false;
		Scanning = false;
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
	if(Alive) {
		DetectionArea->SetSphereRadius(1750.0f);
		Detected = true;
		DelayedRotation = false;
		HP--;
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
	}
}

void AMyEnemy::AttackStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<AMyArcher>(OtherActor);
	if (OtherActor->IsA<AMyArcher>()) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Player has taken Damage"));
		Attacking = true;
		//Attack();
		StopMovement();
	}
}

void AMyEnemy::AttackEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Attacking = false;
	if(MovementStopped){
		StartMovement();
	}

}

//void AMyEnemy::Attack() {
//	if (Attacking) {
//		Player->OnHit();
//	}
//}

void AMyEnemy::StopMovement()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Stopped"));
	MovementStopped = true;

	RevertSpeed = Speed;
	RevertDirection = Direction;
	RevertPlayerLocation = PlayerLocation;

	Speed = 0.0f;
	Direction = FVector::ZeroVector;
	PlayerLocation = FVector::ZeroVector;

}

void AMyEnemy::StartMovement()
{
	MovementStopped = false;

	Speed = RevertSpeed;
	Direction = RevertDirection;
	PlayerLocation = RevertPlayerLocation;
}

void AMyEnemy::Die()
{
	Destroy();
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
	if (Detected && CurrentDistance < TotalDistance && Alive && !MovementStopped && !OnGoingAttackAnim) {
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
	if (MovementStopped) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Stopped"));
	}

	if (!Detected && !EnemyIsHome && HomeCurrentDistance < HomeTotalDistance && Alive && !MovementStopped && !OnGoingAttackAnim) {

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
	}
	else if (DelayedRotation && Alive && !MovementStopped && !OnGoingAttackAnim) {
		SetActorRotation(FRotator(0.0f, HomeRotation.Yaw, 0.0f));
		DelayedRotation = false;
	}
	if (Attacking) {
		Player->OnHit();
	}
	if (Scanning) {
		WallDetectionCheck();
	}
	if (HP == 0 && Alive) {
		Alive = false;
		//StopMovement();
		DetectionArea->SetSphereRadius(0.0f);
		//Mesh->SetSimulatePhysics(true);
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyEnemy::Die, 05.0f, false);
	}
}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

