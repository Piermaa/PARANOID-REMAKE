// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	BoxComp->InitBoxExtent(FVector(150, 100, 100));
	BoxComp->SetCollisionProfileName("Trigger");


	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComp->SetupAttachment(RootComponent);
	ArrowComp->SetRelativeLocation(FVector(0.0f, 50.0f, -100.0f));


	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(ArrowComp);


	Door->SetWorldScale3D(FVector(1.f));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

//	DrawDebugBox(GetWorld(), GetActorLocation(), BoxComp->GetScaledBoxExtent(), 
//		FQuat(GetActorRotation()), FColor::Turquoise, true, 999, 0, 2);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpening)
	{
		OpenDoor(DeltaTime);
	}

	if (bClosing)
	{
		CloseDoor(DeltaTime);
	}

}

void ADoor::DirectionDependantInteract_Implementation(FVector Forward)
{
	ToggleDoor(Forward);
}

void ADoor::ToggleDoor(FVector ForwardVector)
{
	DispatchParanoidEvents();
	
	DotP = FVector::DotProduct(BoxComp->GetForwardVector(), ForwardVector);

	// get 1 or -1 from the the dot product
	PosNeg = FMath::Sign(DotP) * (bInvertedMesh?-1:1);
	
	// degree to clamp at
	MaxDegree = PosNeg * 90.0f;

	// toggle bools
	if(bUseOpenAnimation)
	{
		if (bIsClosed) {
			bIsClosed = false;
			bClosing = false;
			bOpening = true;
		}
		else {
			bOpening = false;
			bIsClosed = true;
			bClosing = true;
		}
	}
	else
	{
		if(bIsClosed)
		{
			bIsClosed=false;
			SetYaw(MaxDegree);
		}
		else
		{
			bIsClosed=true;
			SetYaw(0);
		}
	}
}

void ADoor::OpenDoor(float dt)
{
	DoorCurrentRotation = Door->GetRelativeRotation().Yaw;

	AddRotation = PosNeg * dt * SwingSpeed;

	if (FMath::IsNearlyEqual(DoorCurrentRotation, MaxDegree, 1.5f))
	{
		bClosing = false;
		bOpening = false;
	}
	else if (bOpening)
	{
		const FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
}

void ADoor::CloseDoor(float dt)
{
	DoorCurrentRotation = Door->GetRelativeRotation().Yaw;

	if (DoorCurrentRotation > 0)
	{
		AddRotation = -dt * SwingSpeed;
	}
	else
	{
		AddRotation = dt * SwingSpeed;
	}

	if (FMath::IsNearlyEqual(DoorCurrentRotation, 0.0f, 1.5f))
	{
		bClosing = false;
		bOpening = false;
	}
	else if (bClosing)
	{
		FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
}

void ADoor::SetYaw(const float Yaw) const
{
	FRotator Rotation = Door->GetRelativeRotation();
	Rotation.Yaw=Yaw;
	Door->SetRelativeRotation(Rotation);
}


