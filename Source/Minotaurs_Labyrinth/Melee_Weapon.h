// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Melee_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class MINOTAURS_LABYRINTH_API AMelee_Weapon : public AWeapon
{
	GENERATED_BODY()
	
public:
	AMelee_Weapon();

	UPROPERTY(EditAnywhere, Category = "Melee_Weapon")
	float LastUsedTime; // Время последнего использования оружия

	UPROPERTY(EditAnywhere, Category = "Melee_Weapon")
	float CooldownTime; // Время кулдауна оружия в секундах

	UFUNCTION(BlueprintCallable)
	void AttackNearbyEnemy();

	UFUNCTION(BlueprintCallable)
	bool CanUseWeapon() const;
};
