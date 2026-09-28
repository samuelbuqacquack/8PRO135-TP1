// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceurDAsteroides.h"

// Sets default values
APlaceurDAsteroides::APlaceurDAsteroides()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlaceurDAsteroides::BeginPlay()
{
	Super::BeginPlay();
	
	Place();
	
/*	GetWorld()->GetTimerManager().SetTimer( TimerHandle, this,
		&APlaceurDAsteroides::Place, 0, false); */
}

void APlaceurDAsteroides::Place()
{
	FVector PositionASpawner = FVector(0.0f,0.0f, GetActorLocation().Z);
		
	if (BluePrintAPlacer)
	{
		// Calcule une position au hasard
		if (FMath::RandBool()) // En haut
		{
			PositionASpawner.Y = 1100.0f;
			PositionASpawner.X = FMath::FRandRange(-1900.0f, 1900.0f);
		}
		else
		{
			if (FMath::RandBool()) // À gauche
			{
				PositionASpawner.X = 1900.0f;
			}
			else // À droite
			{
				PositionASpawner.X = -1900.0f;
			}
			PositionASpawner.Y = FMath::FRandRange(0.0f, 1100.0f);
		}
			
		// Rotation initiale au hasard
		const float pitch = FMath::FRandRange(-180.f, 180.f);
		const float yaw = FMath::FRandRange(-180.f, 180.f);
		const float roll = FMath::FRandRange(-180.f, 180.f);
		FRotator RotationAuHasard(pitch, yaw, roll);
			
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
		GetWorld()->SpawnActor<AActor>(BluePrintAPlacer, PositionASpawner, 
			RotationAuHasard, SpawnInfo);
		
		GetWorld()->GetTimerManager().SetTimer( TimerHandle, this,
			&APlaceurDAsteroides::Place, FMath::FRandRange(0.5f, 1.0f), false);
	}
}

// Called every frame
void APlaceurDAsteroides::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

