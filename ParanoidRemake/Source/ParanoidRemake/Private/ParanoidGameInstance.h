// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ParanoidGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UParanoidGameInstance : public UGameInstance
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FParanoidEventDelegate, FName, ParanoidEventName);
	
public:
	FParanoidEventDelegate OnParanoidEvent;
	void CallEvents(FName EventName);
};
