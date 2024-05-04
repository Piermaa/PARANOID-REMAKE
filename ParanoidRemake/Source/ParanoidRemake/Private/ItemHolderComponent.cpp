// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHolderComponent.h"

#include "EConstPE.h"
#include "ParanoidGameInstance.h"

UItemHolderComponent::UItemHolderComponent()
{

}

void UItemHolderComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<UParanoidGameInstance>(GetOwner()->GetGameInstance())->OnConstantParanoidEvent.AddDynamic(
		this,
		&UItemHolderComponent::ClearItemListener
	);
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

void UItemHolderComponent::ClearItemListener(EConstPE ConstPe)
{
	if(ConstPe == EConstPE::ClearHand)
	{
		ClearItem();
	}
}

void UItemHolderComponent::ClearItem()
{
	SetStaticMesh(nullptr);
	for (int i=0;i < GetMaterials().Max();i++)
	{
		SetMaterial(i, nullptr);
	}
}


