// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KeyHolderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STALKINGGAZE_API UKeyHolderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKeyHolderComponent();
	
	UFUNCTION(BlueprintPure)
	bool HasKeys(TArray<FName> Keys);
	UFUNCTION(BlueprintPure)
	TSet<FName> GetHeldKeys();
	UFUNCTION(BlueprintCallable)
	void AddKey(FName NewKey);
	UFUNCTION(BlueprintCallable)
	void ConsumeKeys(TArray<FName> ConsumedKeys);

private:
	TSet<FName> HeldKeys;
	
};
