#pragma once

#include "CoreMinimal.h"
#include "MainHero.h"

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/SphereComponent.h"

#include "DartProjectile.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API ADartProjectile : public AActor
{
	GENERATED_BODY()

public:
	ADartProjectile();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	AActor* Target;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:
	void Launch(const FVector& LaunchVelocity);
};