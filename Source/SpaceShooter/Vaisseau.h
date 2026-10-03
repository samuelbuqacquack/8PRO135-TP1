// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Vaisseau.generated.h"

UCLASS()
class SPACESHOOTER_API AVaisseau : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVaisseau();
	
	// Composantes
	UPROPERTY (BlueprintReadWrite, EditAnywhere)
	USphereComponent* LesCollisions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* LeMaillageStatique;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UFloatingPawnMovement* LeMouvement;
	
	// Choses à spawner
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Projectile;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Particules;

	// Sons à jouer
	UPROPERTY(EditAnywhere)
	USoundBase* SonShoot;
	UPROPERTY(EditAnywhere)
	USoundBase* SonTouche;
	UPROPERTY(EditAnywhere)
	USoundBase* SonMort;
	
	UPROPERTY(BlueprintReadOnly)	
	int32 Chances = 3;
	UPROPERTY(BlueprintReadOnly)
	int32 Points = 0;

	void PerdUneVie();
	void GagneUnPoint();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();
	
	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** MappingContext for player input. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	
	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;
	
	/** Shoot Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* ShootAction;
	
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void Shoot(const FInputActionValue& Value);
	
private:
	bool touche;
	float toucheEnd;
	FTimerHandle TimerHandle;
	void Flashe();
	void Meurt();
};
