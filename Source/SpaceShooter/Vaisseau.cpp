// Fill out your copyright notice in the Description page of Project Settings.


#include "Vaisseau.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MaterialStatsCommon.h"
#include "SpaceShooter.h"
#include "Components/BoxComponent.h"
#include "DataWrappers/ChaosVDParticleDataWrapper.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AVaisseau::AVaisseau()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LaBoiteDeCollision = CreateDefaultSubobject<UBoxComponent>(FName("LaBoiteDeCollision"));
	LaBoiteDeCollision->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	LaBoiteDeCollision->SetupAttachment(RootComponent);
	
	LeMaillageStatique = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeMaillageStatique"));
	LeMaillageStatique->SetupAttachment(LaBoiteDeCollision);
	
	LeMouvement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("LeMouvement"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	PointsDeVie = 10;
}

// Called when the game starts or when spawned
void AVaisseau::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVaisseau::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVaisseau::PerdUneVie()
{
	PointsDeVie--;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OUILLE"));
	if (PointsDeVie <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("POU POU POU"));
	}
}

void AVaisseau::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector MovementDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	
	AddMovementInput(MovementDirection, 50.0f, false);
}

void AVaisseau::Shoot(const FInputActionValue& Value)
{
	if (Projectile)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(Projectile, GetActorLocation() + FVector(0.0f, 200.0f, 0.0f), 
			FRotator(FRotator::ZeroRotator), SpawnInfo);
	}	
}

// Called to bind functionality to input
void AVaisseau::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Get controller
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
	 
		// Create and setup system
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
			
			// Set up action bindings
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVaisseau::Move);
			EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AVaisseau::Shoot);			
		}
	}
	else
	{
		UE_LOG(LogSpaceShooter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

