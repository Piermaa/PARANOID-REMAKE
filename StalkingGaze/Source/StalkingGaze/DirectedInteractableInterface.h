
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


class STALKINGGAZE_API IDirectedInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void DirectionDependantInteract(FVector Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void OnSelect(int32 Type);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void OnDeselect();
};
