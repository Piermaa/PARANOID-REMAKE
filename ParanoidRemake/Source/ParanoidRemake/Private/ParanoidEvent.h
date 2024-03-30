// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParanoidEventInterface.h"
#include "GameFramework/Actor.h"
#include "ParanoidEvent.generated.h"

UCLASS()
class AParanoidEvent : public AActor, public IParanoidEventInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParanoidEvent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Paranoid Event") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void InvokeEvent();
};
