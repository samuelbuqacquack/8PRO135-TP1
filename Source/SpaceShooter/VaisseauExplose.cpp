// Fill out your copyright notice in the Description page of Project Settings.


#include "VaisseauExplose.h"

#include "NiagaraActor.h"
#include "NiagaraComponent.h"


// Sets default values
AVaisseauExplose::AVaisseauExplose()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LesParticules = CreateDefaultSubobject<UNiagaraComponent>(FName("LesParticules"));
	SetRootComponent(LesParticules);
}

// Called when the game starts or when spawned
void AVaisseauExplose::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		&AVaisseauExplose::Meurt, 2.0f, false);
}

void AVaisseauExplose::Meurt()
{
		Destroy();
}

// Called every frame
void AVaisseauExplose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

