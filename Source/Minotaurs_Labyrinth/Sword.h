// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Melee_Weapon.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class MINOTAURS_LABYRINTH_API ASword : public AMelee_Weapon
{
	GENERATED_BODY()

public:
	ASword();

	// Декларация компонента
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* SwordMesh;

	// Установка текстуры меча
	/*UFUNCTION(BlueprintCallable, Category = "Sword")
		void SetSwordTexture(UTexture* Texture);*/


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
	/*UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	bool CanAttack() const;

	UFUNCTION(BlueprintCallable)
	void StartAttackAnimation();

	UFUNCTION(BlueprintCallable)
	void ApplyDamageToEnemies();*/

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
