// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FParanoidEventsBatch.generated.h"

enum class EConstPE : uint8;

USTRUCT(BlueprintType)
struct FParanoidEventsBatch
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<class AParanoidEvent*> ParanoidEvents;

	UPROPERTY(EditAnywhere)
	TArray<FName> ParanoidEventsNames;

	UPROPERTY(EditAnywhere)
	TArray<EConstPE> ConstParanoidEvents;
};
