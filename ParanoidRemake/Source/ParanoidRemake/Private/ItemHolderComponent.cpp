// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHolderComponent.h"

// Sets default values for this component's properties
UItemHolderComponent::UItemHolderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UItemHolderComponent::AddHeldItem(UStaticMesh* ItemStaticMesh, TArray<UMaterialInterface*> StaticMeshMaterials)
{
	if(GetStaticMesh()==nullptr)
	{
		SetStaticMesh(ItemStaticMesh);
		for (int i=0; i < StaticMeshMaterials.Max()-1; i++)
		{
			SetMaterial(i, StaticMeshMaterials[i]);
		}
	}
}


