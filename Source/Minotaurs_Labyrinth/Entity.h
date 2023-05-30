// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Communicator_Interface.h"

#include "GameFramework/Pawn.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Entity.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API AEntity : public APawn, public ICommunicator_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntity();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CollisionCapsule;
	
	UPROPERTY(EditAnywhere, Category = "Entity")
	float health;
	
	UPROPERTY(EditAnywhere, Category = "Entity")
	float defence;
	
	UPROPERTY(EditAnywhere, Category = "Entity")
	float movementSpeed;

	UPROPERTY(EditAnywhere, Category = "Entity")
	float range;

	UPROPERTY(EditAnywhere, Category = "Entity")
	float attackRadius;

	UPROPERTY(EditAnywhere, Category = "Entity")
	float damage;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
		void TakeDamage(float DamageAmount);
	virtual void TakeDamage_Implementation(float DamageAmount) override;
};
