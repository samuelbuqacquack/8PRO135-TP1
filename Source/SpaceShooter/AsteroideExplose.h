// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "AsteroideExplose.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroideExplose : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroideExplose();
	
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* LesParticules;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	void Meurt();
	FTimerHandle TimerHandle;
};
