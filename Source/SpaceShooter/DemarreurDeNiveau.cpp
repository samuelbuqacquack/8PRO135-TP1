// Fill out your copyright notice in the Description page of Project Settings.


#include "DemarreurDeNiveau.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "InstanceDeJeu.h"


// Sets default values
ADemarreurDeNiveau::ADemarreurDeNiveau()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADemarreurDeNiveau::BeginPlay()
{
	Super::BeginPlay();
	
	ACameraActor* LaCamera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	APlayerController* LeJoueur = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// Ajuste la caméra
	if (LaCamera && LeJoueur)
	{
		LeJoueur->SetViewTargetWithBlend(LaCamera, 0.0f, VTBlend_Linear, 0.0f, false);
	}
	if (LeJoueur)
	{
		LeJoueur->bShowMouseCursor = Souris;
	}
	
	if (JoueMusiqueNiveau)
	{
		Cast<UInstanceDeJeu>(GetGameInstance())->PartMusiqueNiveau(VolumeMusique);
	}
	else
	{
		Cast<UInstanceDeJeu>(GetGameInstance())->PauseMusiqueNiveau();
	}
	
	if (LeWidget)
	{
		CreateWidget<UUserWidget>(GetWorld(), LeWidget)->AddToViewport();
	}
}

// Called every frame
void ADemarreurDeNiveau::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

