// Fill out your copyright notice in the Description page of Project Settings.


#include "FootstepsPlayer.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "StalkingGaze\RealisticRunningComponent.h"

UFootstepsPlayer::UFootstepsPlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFootstepsPlayer::BeginPlay()
{
	Super::BeginPlay();
	
    CapsuleComp = Cast<UCapsuleComponent>( GetOwner()->GetComponentByClass<UCapsuleComponent>());

	RealisticRunningComponent = Cast<URealisticRunningComponent>( GetOwner()->GetComponentByClass<URealisticRunningComponent>());
}

void UFootstepsPlayer::HandleFootsteps()
{
	FVector Velocity = GetOwner()->GetVelocity();

	if (Velocity.Z == 0 &&
		(abs(Velocity.X) > 0.2f ||
		 abs(Velocity.Y) > 0.2f ))
	{
		TimeForNextFootsStep =  RealisticRunningComponent->ReachedRunningSpeed() ? DelayBetweenFootstepsRunning : DelayBetweenFootstepsWalking;
		
		NextFootstepTimer += 0.02f;

		if(NextFootstepTimer>=TimeForNextFootsStep)
		{
			PlayFootstepsSound();
		}
	}
	else
	{
		NextFootstepTimer = -FirstStepDelay;
	}
}

void UFootstepsPlayer::PlayFootstepsSound() 
{
	OnFootstepsDelegate.Broadcast();
	NextFootstepTimer=0;
}

bool UFootstepsPlayer::GetSurface(FHitResult& OutHitResult, FVector& FeetLocation)
{
	float DistanceToFloor= CapsuleComp->GetScaledCapsuleHalfHeight();
	FVector Start = GetOwner()->GetActorLocation() + ( -1 * DistanceToFloor * (GetOwner()->GetActorUpVector()));
	FVector End = Start + -1 * 20 * (GetOwner()->GetActorUpVector());
	
	FeetLocation = Start;
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 2);
	
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActor(GetOwner());
	
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, Params);
}