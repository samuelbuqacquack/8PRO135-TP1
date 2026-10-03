// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Engine/GameInstance.h"
#include "InstanceDeJeu.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UInstanceDeJeu : public UGameInstance
{
	GENERATED_BODY()
public:
	void PartMusiqueNiveau(float Volume);
	void PauseMusiqueNiveau();
	
	UPROPERTY(EditAnywhere)
	USoundBase* MusiqueDeNiveau;

private:
	bool MusiqueJoue;
	UPROPERTY()
	UAudioComponent* LAudio;
};
