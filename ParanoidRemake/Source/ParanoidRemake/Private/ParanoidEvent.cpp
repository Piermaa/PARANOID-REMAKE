#include "ParanoidEvent.h"
#include "Components/StaticMeshComponent.h"
#include "ParanoidGameInstance.h"
#include "Components/TextRenderComponent.h"
#include "Components/BillboardComponent.h"
AParanoidEvent::AParanoidEvent()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM"));
	// //RootComponent=StaticMeshComponent;
	// StaticMeshComponent->SetHiddenInGame(true);
	// StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// StaticMeshComponent->SetGenerateOverlapEvents(false);
	//StaticMeshComponent->SetRelativeLocation(FVector(0,0,0));
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SM"));
	RootComponent = BillboardComponent;
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
	TextRenderComponent->SetHiddenInGame(true);
	TextRenderComponent->SetRelativeLocation(FVector(0,0,100));
	TextRenderComponent->SetTextRenderColor(FColor::Green);

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



void AParanoidEvent::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TextRenderComponent->Text=FText::FromName(ParanoidEventName);
	TextRenderComponent->SetVisibility(ShowDebugElements);
	BillboardComponent->SetVisibility(ShowDebugElements);
//	StaticMeshComponent->SetVisibility(ShowDebugElements);
}


void AParanoidEvent::UpdateDebugSymbols_Implementation()
{
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


