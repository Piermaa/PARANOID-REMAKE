// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyLockedActorInterface.h"
#include "KeyUnlockerActor.h"
#include "GameFramework/Actor.h"
#include "ParanoidEventDispatcher.generated.h"

UCLASS()
class AParanoidEventDispatcher : public AActor, public IKeyLockedActorInterface, public IKeyUnlockerActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParanoidEventDispatcher();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool ShowDebugElements = true;

	UPROPERTY(VisibleDefaultsOnly, Category = "Debug")
	class UTextRenderComponent* TextRenderComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Debug")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	FColor DebugLinesColor;

	UFUNCTION(BlueprintCallable, CallInEditor, BlueprintNativeEvent)
	void UpdateDebugSymbols();
	
	UPROPERTY(EditAnywhere, Category = "Paranoid Events")
	TArray<class AParanoidEvent*> ParanoidEvents;

	UPROPERTY(EditAnywhere, Category = "Paranoid Events")
	TArray<FName> ParanoidEventsNames;

	UPROPERTY(EditAnywhere, Category = "Keys")
	TArray<FName> KeysRequired = TArray<FName>();;
	
	UPROPERTY(EditAnywhere, Category = "Keys")
	TArray<FName> KeysToUnlock = TArray<FName>();
	
	UFUNCTION(BlueprintCallable)
	void DispatchParanoidEvents();

	UFUNCTION(BlueprintCallable)
	bool CheckKeys();

	UFUNCTION(BlueprintCallable)
	virtual void KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse) override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<FName> KeysToUnlock_Implementation() override;
};
