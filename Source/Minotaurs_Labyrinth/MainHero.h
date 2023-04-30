// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainHero.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API AMainHero : public APawn
{
	GENERATED_BODY()

public:
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
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Character")
	float MovementSpeed;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForwardBack(float Value);
	void MoveLeftRight(float Value);
	virtual void BeginPlay() override;
};