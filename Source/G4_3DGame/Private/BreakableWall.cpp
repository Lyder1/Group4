// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableWall.h"
#include "Components/SphereComponent.h"

// Sets default values
ABreakableWall::ABreakableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> IntactWall(TEXT("'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BrokenWall(TEXT("'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	BrokenWallMesh = BrokenWall.Object;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetStaticMesh(IntactWall.Object);


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABreakableWall::Explode);

}

// Called when the game starts or when spawned
void ABreakableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableWall::Explode(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Hit"));
	if (OtherComp->ComponentHasTag("Exploded")) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Works"));
		Mesh->SetStaticMesh(BrokenWallMesh);
	}
}



// Called every frame
void ABreakableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

