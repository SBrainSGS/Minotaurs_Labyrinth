// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Melee_Weapon.h"
#include "Axe.generated.h"

/**
 * 
 */
UCLASS()
class MINOTAURS_LABYRINTH_API AAxe : public AMelee_Weapon
{
	GENERATED_BODY()

public:
	AAxe();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* AxeMesh;

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
