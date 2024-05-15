// EDVARD ANDREASSEN


#include "MyArcher.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

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
	ArcherSpringArm->SocketOffset.Set(0, 70.0f, 50.0f);

	saveObj = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadObj = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
}

void AMyArcher::Die()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Dead"));
}

void AMyArcher::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (AnimReadyArrow) {
		MovementVector *= 0.5;
	}

	if (Controller != nullptr) {
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyArcher::OnHit()
{
	if (!Damaged) {
		Damaged = true;
		PlayerHealth--;
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyArcher::DamageDelay, 1.5f, false);
	}
	FString VariableString = FString::Printf(TEXT("Remaining health: %.2f"), PlayerHealth);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, VariableString);
}

void AMyArcher::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAroundVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAroundVector.X);
		AddControllerPitchInput(LookAroundVector.Y);
	}
}

void AMyArcher::InputLoad(const FInputActionValue& Value)
{
	const bool LoadVal = Value.Get<bool>();

	LoadObj = UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0);
	//saveObj = Cast<UMainSaveGame>(LoadObj);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("load a saved game."));

	if (!LoadObj)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Create it "));

		saveObj = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		const bool IsSaved = UGameplayStatics::SaveGameToSlot(saveObj, TEXT("Slot1"), 0);

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT(" Loaded."));
	}

	SetActorLocation(saveObj->PlayerLocation);
	SetActorRotation(saveObj->PlayerRotation);
}

void AMyArcher::SaveGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Saved "));
	saveObj = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	saveObj->PlayerLocation = GetActorLocation();
	saveObj->PlayerRotation = GetActorRotation();
	UGameplayStatics::SaveGameToSlot(saveObj, TEXT("Slot1"), 0);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Data saved ... "));
}

void AMyArcher::DamageDelay()
{
	Damaged = false;
}

void AMyArcher::AttackDelay()
{
	AttackPrimed = true;
}

void AMyArcher::PlayFireAnimation()
{
	AnimFireArrow = false;
	AnimReadyArrow = true;
}


void AMyArcher::FireArrow()
{
	// Attempt to fire a projectile.
	if (Ammo > 0 && AttackPrimed) {
		if (ProjectileClass)
		{
			AnimFireArrow = true;
			AnimReadyArrow = false;
			AttackPrimed = false;
			// Get the camera transform.
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);

			// Set ArrowOrigin to spawn projectiles slightly in front of the camera.
			ArrowOrigin.Set(100.0f, 0.0f, -50.0f);

			// Transform MuzzleOffset from camera space to world space.
			FVector OriginLocation = CameraLocation + FTransform(CameraRotation).TransformVector(ArrowOrigin);

			// Skew the aim to be slightly upwards.
			FRotator OriginRotation = CameraRotation;
			OriginRotation.Pitch += 3.0f;

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				// Spawn the projectile at the muzzle.
				AArrow* Projectile = World->SpawnActor<AArrow>(ProjectileClass, OriginLocation, OriginRotation, SpawnParams);
				if (Projectile)
				{
					// Set the projectile's initial trajectory.
					FVector LaunchDirection = OriginRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
					Ammo--;
				}
			}
			
		}
		GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &AMyArcher::AttackDelay, 1.0f, false);
		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("No Ammo"));
	}

}

// Called when the game starts or when spawned
void AMyArcher::BeginPlay()
{
	//if (PlayerHealth > 0) {
	//	Super::BeginPlay();

	//	// Adding the Input Mapping Context
	//	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//	{
	//		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//		{
	//			Subsystem->AddMappingContext(IMC, 0);
	//		}
	//	}
	//}
	//else {
	//	//Super::EndPlay();
	//}

	Super::BeginPlay();

	// Adding the Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

// Called every frame
void AMyArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerHealth <= 0) {
		Die();
	}
}

// Called to bind functionality to input
void AMyArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyArcher::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyArcher::LookAround);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(LoadAction, ETriggerEvent::Triggered, this, &AMyArcher::InputLoad);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMyArcher::PlayFireAnimation);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AMyArcher::FireArrow);
	}
}

