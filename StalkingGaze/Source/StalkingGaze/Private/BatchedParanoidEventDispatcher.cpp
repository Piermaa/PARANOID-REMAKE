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

void ABatchedParanoidEventDispatcher::TryCallParanoidEvents()
{
	UParanoidGameInstance* GameInstance = Cast<UParanoidGameInstance>(GetGameInstance());

	if(GameInstance->GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
	{
		for (auto KeyToUnlock : KeysToUnlock)
		{
			IKeyHolderActor::Execute_AddKeyToActor(GameInstance, KeyToUnlock);	
		}
		
		if(CheckKeys(GameInstance))
		{
			CallParanoidEvents(GameInstance);
		}
	}
}

bool ABatchedParanoidEventDispatcher::CheckKeys(UGameInstance* P_GameInstance)
{
	if(P_GameInstance->GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
	{
		return IKeyHolderActor::Execute_ActorHasKeys(P_GameInstance, KeysRequired) && ParanoidEventsBatches.IsValidIndex(ParanoidEventsIndex);
	}
	return true;
}

void ABatchedParanoidEventDispatcher::CallParanoidEvents(UParanoidGameInstance* P_GameInstance)
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
		P_GameInstance->CallEvents(EventName);
	}
				
	for (auto ConstEvent :  ParanoidEventsBatches[ParanoidEventsIndex].ConstParanoidEvents)
	{
		P_GameInstance->CallConstEvents(ConstEvent);
	}
			
	OnChangeState();
	ParanoidEventsIndex++;
}

void ABatchedParanoidEventDispatcher::KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse)
{
	KeysRequiredToUse = KeysRequired;
}

TArray<FName> ABatchedParanoidEventDispatcher::KeysToUnlock_Implementation()
{
	return KeysRequired;
}
