// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FParanoidEventsBatch.generated.h"
USTRUCT(BlueprintType)
struct FParanoidEventsBatch
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<class AParanoidEvent*> ParanoidEvents;

	UPROPERTY(EditAnywhere)
	TArray<FName> ParanoidEventsNames;
};
