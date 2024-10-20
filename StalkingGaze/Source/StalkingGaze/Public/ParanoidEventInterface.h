// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ParanoidEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UParanoidEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STALKINGGAZE_API IParanoidEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Paranoid Event") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void TryInvokeEvent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Paranoid Event") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void InvokeEvent();
};
