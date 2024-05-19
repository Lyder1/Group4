// EDVARD ANDREASSEN


#include "Rat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ARat::ARat()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Rat CollisionBox"));
	InteractBox->SetupAttachment(RootComponent);
	
	RatSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	RatSpringArm->SetupAttachment(GetMesh());

	RatCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	RatCamera->AttachToComponent(RatSpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	RatSpringArm->bUsePawnControlRotation = true;
	RatSpringArm->bEnableCameraLag = true;
	RatSpringArm->TargetArmLength = 150.0f;
	RatSpringArm->SocketOffset.Set(0, 0, 50.0f);

}

void ARat::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		FVector Forward = GetActorForwardVector();
		FVector Right = GetActorRightVector();

		FVector Direction = (Forward * MovementVector.Y) + (Right * MovementVector.X);
		Direction.Z = 0.0f;

		if (!Direction.IsNearlyZero())
		{
			FRotator NewRotation = Direction.Rotation();
			NewRotation.Yaw -= 90.0f;
			GetMesh()->SetWorldRotation(NewRotation);
		}

		AddMovementInput(Forward, MovementVector.Y);
		AddMovementInput(Right, MovementVector.X);
	}
}

void ARat::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAroundVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAroundVector.X);
		AddControllerPitchInput(LookAroundVector.Y);
	}
}

void ARat::InteractOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("Overlapping"));
	Interface = Cast<IInteractionInterface>(OtherActor);
}

void ARat::InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, TEXT("Stopped Overlapping"));
	Interface = nullptr;
}

void ARat::InputInteract()
{
	if (Interface)
	{
		Interface->InteractWithThis();
	}
}

// Called when the game starts or when spawned
void ARat::BeginPlay()
{
	Super::BeginPlay();

	// Adding the Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}

	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &ARat::InteractOnOverlap);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &ARat::InteractEnd);
	
}

// Called every frame
void ARat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARat::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARat::LookAround);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ARat::InputInteract);
	}

}

