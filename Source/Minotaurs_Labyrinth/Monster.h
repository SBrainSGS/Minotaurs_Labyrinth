// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"

#include "Entity.h"
#include "MainHero.h"

#include "Monster.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API AMonster : public AEntity
{
	GENERATED_BODY()

protected:
	UFUNCTION(Category = "AI")
	void UpdateAI();

	UFUNCTION(Category = "AI")
	bool CanSeeTarget();

	UFUNCTION(Category = "AI")
	void ChaseTarget();

	UFUNCTION(Category = "AI")
	void AttackTarget();

	UFUNCTION(Category = "AI")
	bool IsInRangeOfTarget();

	UFUNCTION(Category = "AI")
	void StartWander();

	UFUNCTION(Category = "AI")
	void StopWander();

	UPROPERTY(EditAnywhere, Category = "AI")
	APawn* targetEntity;

	UPROPERTY(EditAnywhere, Category = "AI")
	float wanderRadius;

	UPROPERTY(EditAnywhere, Category = "AI")
	float wanderDuration;

	UPROPERTY(EditAnywhere, Category = "AI")
	FTimerHandle WanderTimerHandle;

public:
	AMonster();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
