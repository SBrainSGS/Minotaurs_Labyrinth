// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "EngineUtils.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"

#include "Entity.h"
#include "MainHero.h"

#include "Monster.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API AMonster : public AEntity
{
	GENERATED_BODY()

protected:
	/*UFUNCTION(Category = "AI")
	void ChaseTarget();*/

	UFUNCTION(BlueprintCallable, Category = "AI")
	void AttackTarget();

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool IsInRangeOfTarget();

	UFUNCTION(Category = "AI")
	void StartWander();

	UFUNCTION(Category = "AI")
	void StopWander();

	/*UFUNCTION(BlueprintCallable, Category = "AI")
	void OnSeePawn(APawn* SeenPawn);*/

	UPROPERTY(EditAnywhere, Category = "AI")
	AMainHero* targetEntity;

	UPROPERTY(EditAnywhere, Category = "AI")
	float wanderRadius;

	UPROPERTY(EditAnywhere, Category = "AI")
	float wanderDuration;

	UPROPERTY(EditAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditAnywhere, Category = "AI")
	FTimerHandle WanderTimerHandle;

	UPROPERTY(EditAnywhere, Category = "AI")
	bool IsPlayerSeen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UPathFollowingComponent* PathFollowingComponent;

public:
	AMonster();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
