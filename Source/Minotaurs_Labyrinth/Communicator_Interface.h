#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Communicator_Interface.generated.h"

UINTERFACE(MinimalAPI)
class UCommunicator_Interface : public UInterface
{
	GENERATED_BODY()
};

class MINOTAURS_LABYRINTH_API ICommunicator_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Communicator")
	void Interact();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void TakeDamage(float DamageAmount);
};
