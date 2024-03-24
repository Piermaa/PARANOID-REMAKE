// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "Camera/CameraShake.h"
#include "CameraShakeSelectorComponent.generated.h"


class URealisticRunningComponent;
class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARANOIDREMAKE_API UCameraShakeSelectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraShakeSelectorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SelectCameraShake() const;

public:
	void SetCharacterMovementComponent(UCharacterMovementComponent* NewCharacterMovementComponent, 
		AController* Controller,
		URealisticRunningComponent* NewRealisticRunningComponent);

	UPROPERTY(EditAnywhere, Category = "Camera Shakes")
	TSubclassOf<UCameraShakeBase> IdleCameraShake;
	UPROPERTY(EditAnywhere, Category = "Camera Shakes")
	TSubclassOf<UCameraShakeBase> WalkCameraShake;
	UPROPERTY(EditAnywhere, Category = "Camera Shakes")
	TSubclassOf<UCameraShakeBase> RunCameraShake;

private:
	class UCharacterMovementComponent* CharacterMovementComponent;
	class APlayerController* PlayerController;
	class URealisticRunningComponent* RealisticRunningComponent;
};
