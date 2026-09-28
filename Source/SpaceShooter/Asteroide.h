// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Asteroide.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroide : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroide();
	
	// Composantes
	UPROPERTY (BlueprintReadWrite, EditAnywhere)
	UBoxComponent* LaBoiteDeCollision;
	UPROPERTY (BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* LeMaillageStatique;
	//UPROPERTY (BlueprintReadWrite, EditAnywhere)
	//UPhysicsConstraintComponent* LesContraintesPhysiques;

	// Classes à connaître
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Joueur;
	
	// Variables
	int8 PointsDeVie;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void PasseParDessus(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
