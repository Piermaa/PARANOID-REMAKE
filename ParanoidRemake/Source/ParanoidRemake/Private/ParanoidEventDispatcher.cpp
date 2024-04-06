
#include "ParanoidEventDispatcher.h"
#include "ParanoidEvent.h"
#include "ParanoidEventInterface.h"
#include "ParanoidGameInstance.h"

// Sets default values
AParanoidEventDispatcher::AParanoidEventDispatcher()
{
	PrimaryActorTick.bCanEverTick = true;
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



