

#include "ParanoidEventDispatcher.h"
#include "ParanoidEvent.h"
#include "ParanoidEventInterface.h"

// Sets default values
AParanoidEventDispatcher::AParanoidEventDispatcher()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AParanoidEventDispatcher::DispatchParanoidEvents()
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
}



