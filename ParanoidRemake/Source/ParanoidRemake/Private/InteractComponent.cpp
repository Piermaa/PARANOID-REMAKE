// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractComponent.h"
#include "Camera/CameraComponent.h"
#include "KeyHolderActor.h"
#include "ItemHolderComponent.h"
#include "KeyLockedActorInterface.h"
#include "ParanoidRemake/DirectedInteractableInterface.h"
#include "ParanoidRemake/InteractableInterface.h"
#include "PickupeableInterface.h"


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
}

void UInteractComponent::Interact()
{
	FHitResult HitResult;

	if(GetOwner()->GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
	{
		if (InteractableReached(HitResult))
		{
			AActor* HitActor = HitResult.GetActor();
			UClass* ActorClass= HitActor->GetClass();

			// Chequeo que no esté lockeado
			UE_LOG(LogTemp,Warning, TEXT("Checkeo si esta bloqueado"))
			if(ActorClass->ImplementsInterface(UKeyLockedActorInterface::StaticClass()))
			{
				UE_LOG(LogTemp,Error, TEXT("Esta bloqueado"))
				TArray<FName> KeysRequired = TArray<FName>();
				IKeyLockedActorInterface::Execute_KeysRequiredToUse(HitActor, KeysRequired);
			
				if(!( IKeyHolderActor::Execute_ActorHasKeys(GetOwner(), KeysRequired)))
				{
					return;
				}
			}
			UE_LOG(LogTemp,Warning, TEXT("Checkeo si es interactuable direccional"))
			if(ActorClass->ImplementsInterface(UDirectedInteractableInterface::StaticClass()))
			{
				IDirectedInteractableInterface::Execute_DirectionDependantInteract(HitActor, CameraComp->GetForwardVector());
				UE_LOG(LogTemp,Error, TEXT("Es ii"))
			}
			UE_LOG(LogTemp,Warning, TEXT("Checkeo si es interactuable"))
			// Si es interactuable:
			if (ActorClass->ImplementsInterface(UInteractableInterface::StaticClass()))
			{
				IInteractableInterface::Execute_Interact(HitActor);

				// Si se puede agarrar
				if(ActorClass->ImplementsInterface(UPickupeableInterface::StaticClass()))
				{
					if(ItemHolder==nullptr)
					{
						ItemHolder = GetOwner()->GetComponentByClass<UItemHolderComponent>();
						if(ItemHolder==nullptr) { return; }
					}
					
					TArray<UMaterialInterface*> PickupeableMaterials = TArray<UMaterialInterface*>();
					UStaticMesh* PickupeableMesh = IPickupeableInterface::Execute_Pickup(HitActor, PickupeableMaterials);
					ItemHolder->AddHeldItem(PickupeableMesh, PickupeableMaterials);	
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error,TEXT("Actor does not implement key holder"));
	}
}

bool UInteractComponent::InteractableReached(FHitResult& OutHitResult)
{
	if (CameraComp == nullptr)
	{
		CameraComp = GetOwner()->GetComponentByClass<UCameraComponent>();

		if(CameraComp == nullptr) {return false;} 
	}

	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + CameraComp->GetForwardVector() * InteractionDistance;
	FCollisionQueryParams Params;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 2);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, Params);
}


