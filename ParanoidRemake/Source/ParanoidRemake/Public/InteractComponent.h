// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARANOIDREMAKE_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

	UPROPERTY(EditDefaultsOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 400.0f;
	UPROPERTY(EditDefaultsOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp = nullptr;

	class UItemHolderComponent* ItemHolder;
	
	void Interact();
	bool InteractableReached(FHitResult& OutHitResult);
};
