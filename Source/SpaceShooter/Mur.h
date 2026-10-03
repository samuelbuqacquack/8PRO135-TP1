// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Mur.generated.h"

UCLASS()
class SPACESHOOTER_API AMur : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMur();
	
	// Composants
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* LesCollisions;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void PasseParDessus(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
