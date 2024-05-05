#pragma once

#include "CoreMinimal.h"
#include "KeyLockedActorInterface.h"
#include "KeyUnlockerActor.h"
#include "GameFramework/Actor.h"
#include "ParanoidEventDispatcher.generated.h"


enum class EConstPE:uint8;

UCLASS()
class AParanoidEventDispatcher : public AActor, public IKeyLockedActorInterface, public IKeyUnlockerActor
{
	GENERATED_BODY()
	
public:
	///////////////// UE5 //////////////////
	AParanoidEventDispatcher();
	virtual void OnConstruction(const FTransform& Transform) override;
	////////////////////////////////////////////
	////////////// UPROPERTIES ////////////////
	///////////////////////////////////////////

	///////////////// DEBUG //////////////////
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool ShowDebugElements = true;
	UPROPERTY(VisibleDefaultsOnly, Category = "Debug")
	class UTextRenderComponent* TextRenderComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = "Debug")
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, Category = "Debug")
	FColor DebugLinesColor;

	///////////////// Paranoid //////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paranoid Events")
	TArray<class AParanoidEvent*> ParanoidEvents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paranoid Events")
	TArray<FName> ParanoidEventsNames;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Paranoid Events")
	TArray<EConstPE> ConstParanoidEvents;
	//////////// Keys Interface //////////////
	UPROPERTY(EditAnywhere, Category = "Keys")
	TArray<FName> KeysRequired = TArray<FName>();
	UPROPERTY(EditAnywhere, Category = "Keys")
	bool ConsumeKeys = true;
	UPROPERTY(EditAnywhere, Category = "Keys")
	TArray<FName> KeysToUnlock = TArray<FName>();
		
	////////////////////////////////////////////
	/////////////// UFUNCTION /////////////////
	///////////////////////////////////////////
	
	UFUNCTION(BlueprintCallable)
	void DispatchParanoidEvents();
	UFUNCTION(BlueprintCallable)
	bool CheckKeys(UGameInstance* P_GameInstance);

	//////////// Keys Interface //////////////
	UFUNCTION(BlueprintCallable)
	virtual void KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse) override;
	UFUNCTION(BlueprintCallable)
	virtual TArray<FName> KeysToUnlock_Implementation() override;

	////////// Debug /////////////////////
	UFUNCTION(BlueprintCallable, CallInEditor, BlueprintNativeEvent)
	void UpdateDebugSymbols();
};
