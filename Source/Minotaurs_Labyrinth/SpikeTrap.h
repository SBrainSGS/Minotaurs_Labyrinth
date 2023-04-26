#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "Components/BoxComponent.h"
#include "SpikeTrap.generated.h"

UCLASS()
class MINOTAURS_LABYRINTH_API ASpikeTrap : public ATrap
{
	GENERATED_BODY()

public:
	ASpikeTrap();

protected:
	UPROPERTY(EditAnywhere, Category = "SpikeTrap")
	UStaticMeshComponent* TrapMesh;

	UPROPERTY(EditAnywhere, Category = "SpikeTrap")
	UBoxComponent* TriggerCollisionComponent;

	UFUNCTION()
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