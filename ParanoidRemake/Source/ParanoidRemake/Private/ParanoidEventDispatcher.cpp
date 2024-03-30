

#include "ParanoidEventDispatcher.h"
#include "ParanoidEvent.h"

// Sets default values
AParanoidEventDispatcher::AParanoidEventDispatcher()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AParanoidEventDispatcher::DispatchParanoidEvents()
{
	for (auto ParanoidEvent : ParanoidEvents)
	{
		ParanoidEvent->InvokeEvent();
	}
}



