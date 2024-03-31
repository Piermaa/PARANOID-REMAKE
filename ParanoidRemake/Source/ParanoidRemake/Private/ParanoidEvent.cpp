#include "ParanoidEvent.h"

AParanoidEvent::AParanoidEvent()
{
	PrimaryActorTick.bCanEverTick = true;

}
void AParanoidEvent::TryInvokeEvent_Implementation()
{
	if(InvokeOnce)
	{
		if(!Invoked)
		{
			InvokeEvent();
			Invoked = true;
		}
	}
	else
	{
		InvokeEvent();
	}
}

void AParanoidEvent::InvokeEvent_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("PARANOID EVENT INVOKED"));
}


