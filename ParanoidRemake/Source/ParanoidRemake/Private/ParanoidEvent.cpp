#include "ParanoidEvent.h"

AParanoidEvent::AParanoidEvent()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AParanoidEvent::InvokeEvent_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("PARANOID EVENT INVOKED"));
}


