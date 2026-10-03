// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroideExplose.h"


// Sets default values
AAsteroideExplose::AAsteroideExplose()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LesParticules = CreateDefaultSubobject<UNiagaraComponent>(FName("LesParticules"));
	SetRootComponent(LesParticules);
}

// Called when the game starts or when spawned
void AAsteroideExplose::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		&AAsteroideExplose::Meurt, 2.0f, false);
}

void AAsteroideExplose::Meurt()
{
	Destroy();
}
// Called every frame
void AAsteroideExplose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

