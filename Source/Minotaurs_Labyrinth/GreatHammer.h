// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Melee_Weapon.h"
#include "GreatHammer.generated.h"

/**
 * 
 */
UCLASS()
class MINOTAURS_LABYRINTH_API AGreatHammer : public AMelee_Weapon
{
	GENERATED_BODY()

public:
	AGreatHammer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* SkeletalMesh;

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
