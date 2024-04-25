// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KeyLockedActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKeyLockedActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PARANOIDREMAKE_API IKeyLockedActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Keys")
	void KeysRequiredToUse(TArray<FName>& KeysRequiredToUse);
};
