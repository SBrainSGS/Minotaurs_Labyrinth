#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "Components/BoxComponent.h"
#include "Communicator_Interface.h"
#include "MainHero.h"
#include "Entity.h"
#include "SpikeTrap.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API ASpikeTrap : public ATrap
{
	GENERATED_BODY()

public:
	ASpikeTrap();
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	float damage;

	UPROPERTY(EditAnywhere, Category = "SpikeTrap")
	UBoxComponent* ObjectCollisionComponent;
	
	UPROPERTY(EditAnywhere, Category = "SpikeTrap")
	UBoxComponent* TriggerCollisionComponent;

	UFUNCTION(BlueprintCallable)
	void OnTrapTriggered(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	virtual void BeginPlay() override;
};