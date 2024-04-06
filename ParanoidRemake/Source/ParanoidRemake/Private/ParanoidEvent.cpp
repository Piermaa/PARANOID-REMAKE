#include "ParanoidEvent.h"

#include "ParanoidGameInstance.h"

AParanoidEvent::AParanoidEvent()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AParanoidEvent::BeginPlay()
{
	Super::BeginPlay();
	
	UParanoidGameInstance* GameInstance = Cast<UParanoidGameInstance>(GetGameInstance());
	if(GameInstance!=nullptr)
	{
		GameInstance->OnParanoidEvent.AddDynamic(this, &AParanoidEvent::InvokeEventByName); 
	}
}

void AParanoidEvent::BeginDestroy()
{
	Super::BeginDestroy();
	
}

void AParanoidEvent::InvokeEventByName(FName EventName)
{
	if(EventName==ParanoidEventName)
	{
		TryInvokeEvent();
	}
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


