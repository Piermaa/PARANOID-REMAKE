// Fill out your copyright notice in the Description page of Project Settings.
#include "BatchedParanoidEventDispatcher.h"
#include "KeyHolderActor.h"
#include "ParanoidEvent.h"
#include "ParanoidEventInterface.h"
#include "ParanoidGameInstance.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABatchedParanoidEventDispatcher::ABatchedParanoidEventDispatcher()
{
	PrimaryActorTick.bCanEverTick = true;
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComp"));
	TextRenderComponent->SetupAttachment(Root);
	TextRenderComponent->SetRelativeLocation(FVector(0,0,100));
	TextRenderComponent->SetHiddenInGame(true);
	TextRenderComponent->SetTextRenderColor(FColor::Green);
}

void ABatchedParanoidEventDispatcher::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FlushPersistentDebugLines(GetWorld());
	TextRenderComponent->SetVisibility(ShowDebugElements);
	if(ShowDebugElements)
	{
		UpdateDebugSymbols_Implementation();
	}
}

void ABatchedParanoidEventDispatcher::OnChangeState_Implementation()
{
	UE_LOG(LogTemp,Display,TEXT("My new state"));
}

void ABatchedParanoidEventDispatcher::UpdateDebugSymbols_Implementation()
{
	for (auto Batch : ParanoidEventsBatches)
	{
		for (auto Paranoidevent: Batch.ParanoidEvents)
		{
			if(Paranoidevent!=nullptr)
			{
				
				DrawDebugLine(GetWorld(),
					GetActorLocation(),
					Paranoidevent->GetActorLocation(),
					FColor::Green,
					true
					);
			}

			TextRenderComponent->Text=FText::FromString("");
			FString ParanoidEventNamesListString="";
			for (auto EventNamesListString : ParanoidEventNamesListString)
			{
				for (auto EventName : Batch.ParanoidEventsNames)
				{
					ParanoidEventNamesListString =  ParanoidEventNamesListString + EventName.ToString() + "\n";
				}
			}
			
			TextRenderComponent->Text=FText::FromString(ParanoidEventNamesListString);
		}
	}
}

void ABatchedParanoidEventDispatcher::DispatchParanoidEvents()
{
	UParanoidGameInstance* GameInstance = Cast<UParanoidGameInstance>(GetGameInstance());

	if(CheckKeys())
	{
		if(!ParanoidEventsBatches.IsValidIndex(ParanoidEventsIndex))
		{
			UE_LOG(LogTemp, Error, TEXT("Paranoid event is null"));
		}
		else
		{
			for (auto ParanoidEvent : ParanoidEventsBatches[ParanoidEventsIndex].ParanoidEvents)
			{
				if(ParanoidEvent != nullptr)
				{
					if(ParanoidEvent->GetClass()->ImplementsInterface(UParanoidEventInterface::StaticClass()))
					{
						ParanoidEvent->TryInvokeEvent();
					}
				}
			}

			for (auto EventName :  ParanoidEventsBatches[ParanoidEventsIndex].ParanoidEventsNames)
			{
				GameInstance->CallEvents(EventName);
			}
		
			UObject* PlayerCharacter = Cast<ACharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		
			if(PlayerCharacter-GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
			{
				for (auto KeyToUnlock : KeysToUnlock)
				{
					IKeyHolderActor::Execute_AddKeyToActor(PlayerCharacter, KeyToUnlock);	
				}
			}
		}
		OnChangeState();
		ParanoidEventsIndex++;
	}
}

bool ABatchedParanoidEventDispatcher::CheckKeys()
{
	UE_LOG(LogTemp, Warning,TEXT("Checking KeysRequired in Paranoid Event Dispacher:"));

	FString KeysLen= FString::FromInt(KeysRequired.Max());
	UE_LOG(LogTemp, Error,TEXT("Keys required amount: %s"), *KeysLen);
	if(KeysRequired.Max()==0)
	{
		return true;
	}
	
	UObject* PlayerCharacter = Cast<ACharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(!PlayerCharacter-GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
	{
		return true;
	}

	const bool HasKeys = IKeyHolderActor::Execute_ActorHasKeys(PlayerCharacter, KeysRequired);
	FString Has= HasKeys ? "Has" : "Has Not";
	UE_LOG(LogTemp, Error,TEXT("Has keys: %s"), *Has);
	return HasKeys;
}

void ABatchedParanoidEventDispatcher::KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse)
{
	KeysRequiredToUse = KeysRequired;
}

TArray<FName> ABatchedParanoidEventDispatcher::KeysToUnlock_Implementation()
{
	return KeysRequired;
}
