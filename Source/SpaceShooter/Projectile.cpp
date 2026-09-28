// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/BoxComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LaBoiteDeCollision = CreateDefaultSubobject<UBoxComponent>(FName("LaBoiteDeCollision"));
	LaBoiteDeCollision->SetupAttachment(RootComponent);
	
	LeMaillageStatique = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeMaillageStatique"));
	LeMaillageStatique->SetupAttachment(LaBoiteDeCollision);	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	LeMaillageStatique->SetPhysicsLinearVelocity(FVector(0.0f, 4000.0f, 0.0f));
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

