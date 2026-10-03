// Fill out your copyright notice in the Description page of Project Settings.


#include "Fond.h"


// Sets default values
AFond::AFond()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LeMaillageStatique = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeMaillageStatique"));
	SetRootComponent(LeMaillageStatique);
}

// Called when the game starts or when spawned
void AFond::BeginPlay()
{
	Super::BeginPlay();
	
	// Pivote
	LeMaillageStatique->SetPhysicsAngularVelocityInDegrees(
		FVector(0.0f, 0.0f, 180.0f), false);
}

// Called every frame
void AFond::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

