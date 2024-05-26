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
	bool DebugLine= false;
	UPROPERTY(EditDefaultsOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp = nullptr;
	class UItemHolderComponent* ItemHolder;

	UFUNCTION(BlueprintCallable)
	void Interact();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool InteractableReached(FHitResult& OutHitResult, bool DrawsDebugLine);
	
	void CallInteract(UObject* Object);
};
