// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KeyHolderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARANOIDREMAKE_API UKeyHolderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKeyHolderComponent();
	bool HasKeys(TArray<FName> Keys);
	TSet<FName> GetHeldKeys();
	void AddKey(FName NewKey);
	void ConsumeKeys(TArray<FName> ConsumedKeys);

private:
	TSet<FName> HeldKeys;
	
};
