
#include "ParanoidEventDispatcher.h"
#include "KeyHolderActor.h"
#include "ParanoidEvent.h"
#include "ParanoidEventInterface.h"
#include "ParanoidGameInstance.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
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

void AParanoidEventDispatcher::DispatchParanoidEvents()
{
	UParanoidGameInstance* GameInstance = Cast<UParanoidGameInstance>(GetGameInstance());

	if(CheckKeys(GameInstance))
	{
		if(GameInstance->GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
		{
			if(!IKeyHolderActor::Execute_ActorHasKeys(GameInstance, KeysRequired))
			{
				return;
			}
			
			for (auto KeyToUnlock : KeysToUnlock)
			{
				IKeyHolderActor::Execute_AddKeyToActor(GameInstance, KeyToUnlock);	
			}
			if(ConsumeKeys)
			{
				IKeyHolderActor::Execute_ConsumeKeysFromActor(GameInstance, KeysRequired);
			}
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
			GameInstance->CallEvents(EventName);
		}
		for (auto ConstEvent :ConstParanoidEvents)
		{
			GameInstance->CallConstEvents(ConstEvent);
		}
	}
}

bool AParanoidEventDispatcher::CheckKeys(UGameInstance* P_GameInstance)
{
	if(P_GameInstance->GetClass()->ImplementsInterface(UKeyHolderActor::StaticClass()))
	{
		UE_LOG(LogTemp,Warning,TEXT("implements"));
		return IKeyHolderActor::Execute_ActorHasKeys(P_GameInstance, KeysRequired);
	}
	UE_LOG(LogTemp,Error,TEXT("Dosent implement"));
	return true;
}

void AParanoidEventDispatcher::KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse)
{
	KeysRequiredToUse = KeysRequired;
}


TArray<FName> AParanoidEventDispatcher::KeysToUnlock_Implementation()
{
	return KeysToUnlock;
}



