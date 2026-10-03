// Fill out your copyright notice in the Description page of Project Settings.


#include "Mur.h"

#include "Asteroide.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"


// Sets default values
AMur::AMur()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LesCollisions = CreateDefaultSubobject<UBoxComponent>(FName("LesCollisions"));
	LesCollisions->SetupAttachment(RootComponent);
	
	// Lie la fonction d'overlap à son événement
	LesCollisions->OnComponentBeginOverlap.AddDynamic(this,&AMur::PasseParDessus);
}

void AMur::PasseParDessus(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AProjectile>(OtherActor) || Cast<AAsteroide>(OtherActor))
	{
		OtherActor->Destroy();
	}
}

// Called when the game starts or when spawned
void AMur::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

