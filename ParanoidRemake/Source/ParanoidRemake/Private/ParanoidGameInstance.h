// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyHolderActor.h"
#include "Engine/GameInstance.h"
#include "EConstPE.h"
#include "ParanoidGameInstance.generated.h"


UCLASS()
class UParanoidGameInstance : public UGameInstance, public IKeyHolderActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FParanoidEventDelegate, FName, ParanoidEventName);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConstParanoidEventDelegate, EConstPE, ConstParanoidEvent);
	
public:
	UPROPERTY(BlueprintAssignable, Category="Delegates")
	FParanoidEventDelegate OnParanoidEvent;
	UPROPERTY(BlueprintAssignable, Category="Delegates")
	FConstParanoidEventDelegate OnConstantParanoidEvent;
	
	UFUNCTION(BlueprintCallable)
	void CallEvents(FName EventName);
	UFUNCTION(BlueprintCallable)
	void CallConstEvents(EConstPE ConstEvent);
	UFUNCTION(BlueprintCallable)
	void ClearKeys();
public:
	virtual TSet<FName> GetKeysFromActor_Implementation() override;
	virtual void AddKeyToActor_Implementation(FName NewKey) override;
	virtual void ConsumeKeysFromActor_Implementation(const TArray<FName>& KeysToConsume) override;
	virtual bool ActorHasKeys_Implementation(const TArray<FName>& KeysToCheck) override;
	
	private:
	TArray<FName> Keys;
};
