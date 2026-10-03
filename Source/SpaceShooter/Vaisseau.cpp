// Fill out your copyright notice in the Description page of Project Settings.


#include "Vaisseau.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SpaceShooter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AVaisseau::AVaisseau()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LesCollisions = CreateDefaultSubobject<USphereComponent>(FName("LesCollisions"));
	SetRootComponent(LesCollisions);
	
	LeMaillageStatique = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeMaillageStatique"));
	LeMaillageStatique->SetupAttachment(LesCollisions);
	
	LeMouvement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("LeMouvement"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
	if (!touche)
	{
		Chances--;
		if (Chances <= 0) // Meurt
		{
			if (SonMort)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), SonMort, 1.0f, 1.0f, 0.0f);				
			}
			if (Particules)
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				GetWorld()->SpawnActor<AActor>(Particules, GetActorLocation(), 
					FRotator(FRotator::ZeroRotator), SpawnInfo);
			}
			SetActorLocation(GetActorLocation() - FVector(0.0f, 0.0f, 1000.0f));
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
				&AVaisseau::Meurt, 2, false);
		}
		else // Flashe
		{
			touche = true;
			toucheEnd = GetWorld()->GetTimeSeconds() + 1.5f;
			if (SonTouche)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), SonTouche, 0.5f, 1.0f, 0.0f);
			}
			Flashe();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
				&AVaisseau::Flashe, 0.05f, true);
		}
	}
}

void AVaisseau::Flashe()
{
	if (GetWorld()->GetTimeSeconds() >= toucheEnd)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		touche = false;
		LeMaillageStatique->SetVisibility(true);
	}
	else
	{
		LeMaillageStatique->SetVisibility(!LeMaillageStatique->IsVisible());
	}
}

void AVaisseau::Meurt()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	UGameplayStatics::OpenLevel(this, FName("Accueil"), true);
}

void AVaisseau::GagneUnPoint()
{
	Points++;
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
		if (SonShoot)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), SonShoot, 0.4f, 1.0f, 0.0f);
		}
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

