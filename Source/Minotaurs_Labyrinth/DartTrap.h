#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "MainHero.h"

#include "Components/BoxComponent.h"

#include "DartTrap.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API ADartTrap : public ATrap
{
	GENERATED_BODY()

public:
	ADartTrap();

protected:
	UPROPERTY(EditAnywhere, Category = "DartTrap")
	UBoxComponent* ObjectCollisionComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, Category = "DartTrap")
	UBoxComponent* TriggerCollisionComponent;

	UPROPERTY(EditAnywhere, Category = "DartTrap")
	float DartDamage;

	UPROPERTY(EditAnywhere, Category = "DartTrap")
	float DartSpeed;

	UPROPERTY(EditAnywhere, Category = "DartTrap")
	float DartLifeSpan;

	FTimerHandle DamageTimerHandle;

	UFUNCTION()
	void OnTrapTriggered(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void SpawnDart(FVector StartLocation, FVector TargetLocation);

	void ApplyDamageToActor(AActor* Actor);

	void OnDartHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void StartDamageTimer();

	void StopDamageTimer();

	void ApplyPeriodicDamage();

	virtual void BeginPlay() override;
};
