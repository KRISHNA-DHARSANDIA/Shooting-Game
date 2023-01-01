// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAlController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_GAME_API AShooterAlController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds);
	
protected:

	virtual void BeginPlay() override;

private:

	// UPROPERTY(EditAnywhere)
	// float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};




