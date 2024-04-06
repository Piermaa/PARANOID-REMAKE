// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FootstepsPlayer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARANOIDREMAKE_API UFootstepsPlayer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootstepsPlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFootstepDelegate);
	
	UPROPERTY(EditAnywhere)
	float DelayBetweenFootstepsWalking=0.5f;

	UPROPERTY(EditAnywhere)
	float DelayBetweenFootstepsRunning=0.25f;
	
	UPROPERTY(EditAnywhere)
	float FirstStepDelay=0.5f;

	UPROPERTY(EditAnywhere)
	float SpeedUmbral;
	
	class UCapsuleComponent* CapsuleComp;

	void PlayFootstepsSound();

	UPROPERTY(BlueprintAssignable, Category = "Footsteps")
	FFootstepDelegate OnFootstepsDelegate;
	
	FTimerHandle FootstepTimerHandle;

	void HandleFootsteps();
	
private:
	bool GetSurface(FHitResult& OutHitResult, FVector& OutFeetLocation);

	bool FootstepsPlayerEnabled = false;

	float TimeForNextFootsStep;

	float NextFootstepTimer;
	
	class URealisticRunningComponent* RealisticRunningComponent;
};