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
	
	if (InteractableReached(HitResult, DebugLine))
	{
		CallInteract(HitResult.GetComponent());
		CallInteract(HitResult.GetActor());
	}
}

bool UInteractComponent::InteractableReached(FHitResult& OutHitResult, bool DrawsDebugLine)
{
	if (CameraComp == nullptr)
	{
		CameraComp = GetOwner()->GetComponentByClass<UCameraComponent>();

		if(CameraComp == nullptr) {return false;} 
	}

	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + CameraComp->GetForwardVector() * InteractionDistance;
	FCollisionQueryParams Params;
	if(DrawsDebugLine)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 2);
	}
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, Params);
}

void UInteractComponent::CallInteract(UObject* Object)
{
	UClass* ObjectClass = Object->GetClass();
	UE_LOG(LogTemp,Warning, TEXT("Checkeo si esta bloqueado"))
	if(ObjectClass->ImplementsInterface(UKeyLockedActorInterface::StaticClass()))
	{
		UE_LOG(LogTemp,Error, TEXT("Esta bloqueado"))
		TArray<FName> KeysRequired = TArray<FName>();
		IKeyLockedActorInterface::Execute_KeysRequiredToUse(Object, KeysRequired);
			
		if(!(IKeyHolderActor::Execute_ActorHasKeys(GetWorld()->GetGameInstance(), KeysRequired)))
		{
			return;
		}
	}
			
	UE_LOG(LogTemp,Warning, TEXT("Checkeo si es interactuable direccional"))
	if(ObjectClass->ImplementsInterface(UDirectedInteractableInterface::StaticClass()))
	{
		IDirectedInteractableInterface::Execute_DirectionDependantInteract(Object, CameraComp->GetForwardVector());
		UE_LOG(LogTemp,Error, TEXT("Es ii"))
	}
	UE_LOG(LogTemp,Warning, TEXT("Checkeo si es interactuable"))
	// Si es interactuable:
	if (ObjectClass->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		IInteractableInterface::Execute_Interact(Object);

		// Si se puede agarrar
		if(ObjectClass->ImplementsInterface(UPickupeableInterface::StaticClass()))
		{
			if(ItemHolder==nullptr)
			{
				ItemHolder = GetOwner()->GetComponentByClass<UItemHolderComponent>();
				if(ItemHolder==nullptr) { return; }
			}
			
			TArray<UMaterialInterface*> PickupeableMaterials = TArray<UMaterialInterface*>();
			FTransform PickupTransform = FTransform();
			UStaticMesh* PickupeableMesh = IPickupeableInterface::Execute_Pickup(Object, PickupeableMaterials, PickupTransform);
			ItemHolder->AddHeldItem(PickupeableMesh, PickupeableMaterials, PickupTransform);	
		}
	}
}



