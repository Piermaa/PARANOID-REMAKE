// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParanoidEventDispatcher.generated.h"

UCLASS()
class AParanoidEventDispatcher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParanoidEventDispatcher();

	UPROPERTY(EditAnywhere, Category = "Paranoid Events")
	TArray<class AParanoidEvent*> ParanoidEvents;

	UFUNCTION(BlueprintCallable)
	void DispatchParanoidEvents();
};
