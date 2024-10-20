// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FParanoidEventsBatch.generated.h"

enum class EConstPE : uint8;

USTRUCT(BlueprintType)
struct FParanoidEventsBatch
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AParanoidEvent*> ParanoidEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> ParanoidEventsNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EConstPE> ConstParanoidEvents;

	// Default constructor
	FParanoidEventsBatch()
	{
		// Ensure arrays are properly initialized
		ParanoidEvents.Empty();
		ParanoidEventsNames.Empty();
		ConstParanoidEvents.Empty();
	}
};
