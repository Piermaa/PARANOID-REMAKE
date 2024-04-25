
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

		TextRenderComponent->Text=FText::FromString("");
		FString ParanoidEventNamesListString="";
		for (auto EventName : ParanoidEventsNames)
		{
			ParanoidEventNamesListString =  ParanoidEventNamesListString + EventName.ToString() + "\n";
		}

		TextRenderComponent->Text=FText::FromString(ParanoidEventNamesListString);
	}
}

void AParanoidEventDispatcher::DispatchParanoidEvents()
{
	UParanoidGameInstance* GameInstance = Cast<UParanoidGameInstance>(GetGameInstance());

	if(CheckKeys())
	{
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
		
		UObject* PlayerCharacter = Cast<ACharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		
		for (auto KeyToUnlock : KeysToUnlock)
		{
			IKeyHolderActor::Execute_AddKeyToActor(PlayerCharacter, KeyToUnlock);	
		}
	}
}

bool AParanoidEventDispatcher::CheckKeys()
{
	UE_LOG(LogTemp, Warning,TEXT("Checking KeysRequired in Paranoid Event Dispacher:"));

	FString KeysLen= FString::FromInt(KeysRequired.Max());
	UE_LOG(LogTemp, Error,TEXT("Keys required amount: %s"), *KeysLen);
	if(KeysRequired.Max()==0)
	{
		return true;
	}
	
	UObject* PlayerCharacter = Cast<ACharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	const bool HasKeys = IKeyHolderActor::Execute_ActorHasKeys(PlayerCharacter, KeysRequired);
	FString Has= HasKeys ? "Has" : "Has Not";
	UE_LOG(LogTemp, Error,TEXT("Has keys: %s"), *Has);
	return HasKeys;
}

void AParanoidEventDispatcher::KeysRequiredToUse_Implementation(TArray<FName>& KeysRequiredToUse)
{
	KeysRequiredToUse = KeysRequired;
}


TArray<FName> AParanoidEventDispatcher::KeysToUnlock_Implementation()
{
	return KeysToUnlock;
}



