// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemarreurDeNiveau.generated.h"

UCLASS()
class SPACESHOOTER_API ADemarreurDeNiveau : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemarreurDeNiveau();
	
	UPROPERTY(EditAnywhere)
	bool Souris;
	UPROPERTY(EditAnywhere)
	bool JoueMusiqueNiveau;
//	UPROPERTY(EditAnywhere)
//	USoundBase* LaMusique;
	UPROPERTY(EditAnywhere)
	float VolumeMusique = 0.75f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LeWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
