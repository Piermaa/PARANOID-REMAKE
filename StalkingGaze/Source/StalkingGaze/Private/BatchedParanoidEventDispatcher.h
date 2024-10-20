// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyLockedActorInterface.h"
#include "KeyUnlockerActor.h"
#include "ParanoidGameInstance.h"
#include "StalkingGaze/Public/Structs/FParanoidEventsBatch.h"
#include "BatchedParanoidEventDispatcher.generated.h"



UCLASS()
class STALKINGGAZE_API ABatchedParanoidEventDispatcher : public AActor, public IKeyLockedActorInterface, public IKeyUnlockerActor
{
	GENERATED_BODY()

public:
	ABatchedParanoidEventDispatcher();

	////////////////////////////////////////////
	////////////// UPROPERTIES ////////////////
	///////////////////////////////////////////

	///////////////// DEBUG //////////////////
	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category ="ParanoidEvents")
	void OnChangeState();
	
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

	UPROPERTY(EditAnywhere, Category = "Keys")
	TArray<FName> KeysRequired = TArray<FName>();;
	
	UPROPERTY(EditAnywhere, Category = "Keys")
	TArray<FName> KeysToUnlock = TArray<FName>();

	
	UFUNCTION(BlueprintCallable)
	void TryCallParanoidEvents();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CheckKeys(UGameInstance* P_GameInstance);
	UFUNCTION(BlueprintCallable)
	void CallParanoidEvents(UParanoidGameInstance* P_GameInstance);

	UFUNCTION(BlueprintCallable)
	virtual void KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse) override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<FName> KeysToUnlock_Implementation() override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TArray<FParanoidEventsBatch> ParanoidEventsBatches = TArray<FParanoidEventsBatch>();

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	int ParanoidEventsIndex;
};
