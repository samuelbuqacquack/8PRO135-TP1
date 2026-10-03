// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanceDeJeu.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UInstanceDeJeu::PartMusiqueNiveau(float Volume)
{
	if (!MusiqueJoue && MusiqueDeNiveau)
	{
		if (!LAudio)
		{
			LAudio = UGameplayStatics::CreateSound2D(GetWorld(), MusiqueDeNiveau, Volume, 1.0f, 0.0f, nullptr, true, false);
			LAudio->Play(0.0f);
		}
		else
		{
			LAudio->SetPaused(false);
		}
		MusiqueJoue = true;
	}
}

void UInstanceDeJeu::PauseMusiqueNiveau()
{
	if (LAudio && MusiqueJoue)
	{
		LAudio->SetPaused(true);
		MusiqueJoue = false;
	}
}
