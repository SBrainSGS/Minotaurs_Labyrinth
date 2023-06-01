// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Engine.h"

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Camera/CameraComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Communicator_Interface.h"
#include "Sword.h"

#include "MainHero.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API AMainHero : public APawn,  public ICommunicator_Interface
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Main Hero")
	UAnimBlueprint* MainHeroAnimBlueprint;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	AMainHero();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CollisionCapsule;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* InteractionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* CharacterMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Character")
	float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* FloatingPawnMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool InCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	AActor* InteractingActor;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	ASword* Sword;

	UPROPERTY(EditAnywhere, Category = "Character")
	float health;

	UPROPERTY(EditAnywhere, Category = "Character")
	float mana;

	UPROPERTY(EditAnywhere, Category = "Character")
	float defence;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = "Character")
    bool bIsDead;
	
	void OnInteractionPressed();

	UFUNCTION(BlueprintCallable)
	void OnLeftClick();

	UFUNCTION(BlueprintCallable)
	void OnInteractionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void TakeDamage(float DamageAmount);
	virtual void TakeDamage_Implementation(float DamageAmount) override;

	UFUNCTION(BlueprintCallable, Category="MainHero")
	float GetHealth();

	UFUNCTION(BlueprintCallable, Category="MainHero")
	float GetMana();
	
	UFUNCTION(BlueprintCallable, Category = "MainHero")
	bool GetIsDead();
	
protected:
	void MoveForwardBack(float Value);
	void MoveLeftRight(float Value);
	
	virtual void BeginPlay() override;
};