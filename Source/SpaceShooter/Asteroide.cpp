// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroide.h"

#include "Projectile.h"
#include "Vaisseau.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAsteroide::AAsteroide()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LesCollisions = CreateDefaultSubobject<USphereComponent>(FName("LesCollisions"));
	SetRootComponent(LesCollisions);

	LeMaillageStatique = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeMaillageStatique"));
	LeMaillageStatique->SetupAttachment(LesCollisions);
	
	FRandomStream Stream(FPlatformTime::Seconds());
	Energie = Stream.RandRange(0,3);
}

// Called when the game starts or when spawned
void AAsteroide::BeginPlay()
{
	Super::BeginPlay();
	
	LeVaisseau = Cast<AVaisseau>(UGameplayStatics::GetActorOfClass(GetWorld(), AVaisseau::StaticClass()));
	
	// Lie la fonction d'overlap à son événement
	LesCollisions->OnComponentBeginOverlap.AddDynamic(this,&AAsteroide::PasseParDessus);
	
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
	float Vitesse = Stream.FRandRange(500.0f, 1500.0f);
	
	// Pivote au hasard	
	LesCollisions->SetPhysicsAngularVelocityInDegrees(
		FVector(
			Stream.FRandRange(0.0f, 180.0f),
			Stream.FRandRange(0.0f, 180.0f),
			Stream.FRandRange(0.0f, 180.0f)),
		false);
	
	LesCollisions->SetPhysicsLinearVelocity(Direction * Vitesse);
}

void AAsteroide::PasseParDessus(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AVaisseau>(OtherActor) == LeVaisseau)
	{
		if (LeVaisseau)
		{
			LeVaisseau->PerdUneVie();
		}
	}
	else if (AProjectile* UnProjectile = Cast<AProjectile>(OtherActor)){
		UnProjectile->Destroy();
		Energie--;
		if (Energie <= 0)
		{
			if (LeVaisseau)
			{
				LeVaisseau->GagneUnPoint();
			}
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
			Destroy();
		}
	}
}

// Called every frame
void AAsteroide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

