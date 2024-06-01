
#include "ParanoidEventDispatcher.h"
#include "KeyHolderActor.h"
#include "ParanoidEvent.h"
#include "ParanoidEventInterface.h"
#include "ParanoidGameInstance.h"
#include "Components/TextRenderComponent.h"
// Sets default values
AParanoidEventDispatcher::AParanoidEventDispatcher()
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

void AParanoidEventDispatcher::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FlushPersistentDebugLines(GetWorld());
	TextRenderComponent->SetVisibility(ShowDebugElements);
	if(ShowDebugElements)
	{
		UpdateDebugSymbols_Implementation();
	}
}

void AParanoidEventDispatcher::UpdateDebugSymbols_Implementation()
{
	for (auto Paranoidevent: ParanoidEvents)
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

		if(!ParanoidEventsNames.IsEmpty())
		{
			TextRenderComponent->Text=FText::FromString("");
			FString ParanoidEventNamesListString="";
			for (auto EventName : ParanoidEventsNames)
			{
				ParanoidEventNamesListString =  ParanoidEventNamesListString + EventName.ToString() + "\n";
			}

			TextRenderComponent->Text=FText::FromString(ParanoidEventNamesListString);
		}
	}
}

void AParanoidEventDispatcher::TryDispatchParanoidEvents()
{
	UParanoidGameInstance* GameInstance = Cast<UParanoidGameInstance>(GetGameInstance());

	if(CheckKeys(GameInstance))
	{
		InvokeParanoidEvents(GameInstance);
	}
}

bool AParanoidEventDispatcher::CheckKeys(UGameInstance* P_GameInstance)
{
	if(P_GameInstance->GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
	{
		return IKeyHolderActor::Execute_ActorHasKeys(P_GameInstance, KeysRequired);
	}
	return true;
}

void AParanoidEventDispatcher::InvokeParanoidEvents(UParanoidGameInstance* P_GameInstance)
{
	for (auto KeyToUnlock : KeysToUnlock)
	{
		IKeyHolderActor::Execute_AddKeyToActor(P_GameInstance, KeyToUnlock);	
	}
	if(ConsumeKeys)
	{
		IKeyHolderActor::Execute_ConsumeKeysFromActor(P_GameInstance, KeysRequired);
	}
		
	for (auto ParanoidEvent : ParanoidEvents)
	{
		if(ParanoidEvent != nullptr)
		{
			if(ParanoidEvent->GetClass()->ImplementsInterface(UParanoidEventInterface::StaticClass()))
			{
				ParanoidEvent->TryInvokeEvent();
			}
		}
	}

	for (auto EventName : ParanoidEventsNames)
	{
		P_GameInstance->CallEvents(EventName);
	}
	for (auto ConstEvent :ConstParanoidEvents)
	{
		P_GameInstance->CallConstEvents(ConstEvent);
	}
}

void AParanoidEventDispatcher::InvokeBatch(UParanoidGameInstance* P_GameInstance, FParanoidEventsBatch BatchToInvoke)
{
	for (auto ParanoidEvent : BatchToInvoke.ParanoidEvents)
	{
		if(ParanoidEvent != nullptr)
		{
			if(ParanoidEvent->GetClass()->ImplementsInterface(UParanoidEventInterface::StaticClass()))
			{
				ParanoidEvent->TryInvokeEvent();
			}
		}
	}

	for (auto EventName : BatchToInvoke.ParanoidEventsNames)
	{
		P_GameInstance->CallEvents(EventName);
	}
	for (auto ConstEvent : BatchToInvoke.ConstParanoidEvents)
	{
		P_GameInstance->CallConstEvents(ConstEvent);
	}
}

void AParanoidEventDispatcher::KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse)
{
	KeysRequiredToUse = KeysRequired;
}


TArray<FName> AParanoidEventDispatcher::KeysToUnlock_Implementation()
{
	return KeysToUnlock;
}



