
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DirectedInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDirectedInteractableInterface : public UInterface
{
	GENERATED_BODY()
};


class PARANOIDREMAKE_API IDirectedInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void DirectionDependantInteract(FVector Direction);
};
