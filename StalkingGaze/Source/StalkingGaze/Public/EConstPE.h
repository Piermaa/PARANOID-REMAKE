// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EConstPE.generated.h"


UENUM(BlueprintType)
enum class EConstPE : uint8
{
 None,
 ReturnToPlayer,
 ClearHand
};