// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InteractableActor.generated.h"

UCLASS()
class PARANOIDREMAKE_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableActor();

public:
	virtual void Interact_Implementation() override;
};
