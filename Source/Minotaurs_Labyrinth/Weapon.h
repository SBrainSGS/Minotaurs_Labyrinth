// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FString name;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int damage;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float radiusAttack;

	UPROPERTY(EditAnywhere, Category = "Melee_Weapon")
	FName Socket; // Сокет персонажа, куда прикреплять оружие

	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FName GetSocket();
	FString GetName();
};
