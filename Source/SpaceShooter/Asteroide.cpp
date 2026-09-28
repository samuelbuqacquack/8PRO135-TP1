// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroide.h"

#include <string>

#include "BlendSpaceAnalysis.h"
#include "Vaisseau.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"


// Sets default values
AAsteroide::AAsteroide()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LaBoiteDeCollision = CreateDefaultSubobject<UBoxComponent>(FName("LaBoiteDeCollision"));
	LaBoiteDeCollision->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));	
	LaBoiteDeCollision->SetupAttachment(RootComponent);
	
	LeMaillageStatique = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeMaillageStatique"));
	LeMaillageStatique->SetupAttachment(LaBoiteDeCollision);
	
	//LesContraintesPhysiques->SetupAttachment(RootComponent);
	
	FRandomStream Stream(FPlatformTime::Seconds());
	PointsDeVie = Stream.RandRange(0,10);
}

// Called when the game starts or when spawned
void AAsteroide::BeginPlay()
{
	Super::BeginPlay();
	
	// Lie la fonction d'overlap à son événement
	LaBoiteDeCollision->OnComponentBeginOverlap.AddDynamic(this,&AAsteroide::PasseParDessus);
	
	FRandomStream Stream(FPlatformTime::Seconds());
	
	// Choisit une cible
	FVector PositionCible;
	if (Stream.RandBool() && Joueur && UGameplayStatics::GetActorOfClass(GetWorld(), Joueur))
	{ // Le joueur
		AActor* leJoueur = UGameplayStatics::GetActorOfClass(GetWorld(), Joueur);
		if (leJoueur)
		{
			PositionCible = leJoueur->GetActorLocation();
		}
	} else // Position au hasard
	{
		PositionCible.X =  Stream.FRandRange(-1700.0f, 1700.0f);
		PositionCible.Y =  Stream.FRandRange(-900.0f, 0.0f);
		PositionCible.Z = GetActorLocation().Z;
	}
	FVector Direction = PositionCible - GetActorLocation();
	Direction.Normalize();

	// Calcule la vitesse
	float Vitesse = Stream.FRandRange(500.0f, 2000.0f);
	
	LaBoiteDeCollision->SetPhysicsLinearVelocity(Direction * Vitesse);
}

void AAsteroide::PasseParDessus(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AVaisseau* leVaisseau = Cast<AVaisseau>(OtherActor))
	{
		leVaisseau->PerdUneVie();
	}
	else
	{
		Destroy();
	}
}

// Called every frame
void AAsteroide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

