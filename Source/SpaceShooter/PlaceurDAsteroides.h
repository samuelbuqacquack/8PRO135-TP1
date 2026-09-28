// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceurDAsteroides.generated.h"

UCLASS()
class SPACESHOOTER_API APlaceurDAsteroides : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlaceurDAsteroides();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Choses à faire apparaître
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BluePrintAPlacer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;
	void Place();
};
