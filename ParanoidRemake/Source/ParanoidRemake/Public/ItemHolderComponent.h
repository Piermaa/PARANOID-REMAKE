// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ItemHolderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARANOIDREMAKE_API UItemHolderComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemHolderComponent();

	void AddHeldItem(UStaticMesh* ItemStaticMesh, TArray<UMaterialInterface*> StaticMeshMaterials);
};
