// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KeyHolderActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UKeyHolderActor : public UInterface
{
	GENERATED_BODY()
};

class PARANOIDREMAKE_API IKeyHolderActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Keys")
	TSet<FName> GetKeysFromActor();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Keys")
	void AddKeyToActor(FName NewKey);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Keys")
	void ConsumeKeysFromActor(const TArray<FName>& KeysToConsume);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Keys")
	bool ActorHasKeys(const TArray<FName>& KeysToCheck);
};
