
#include "ParanoidEventDispatcher.h"
#include "ParanoidEvent.h"
#include "ParanoidEventInterface.h"
#include "ParanoidGameInstance.h"
#include "VectorTypes.h"
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
}



