
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"
UCLASS()
class PARANOIDREMAKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComp;
	
	//###############
	//###Functions###
	//###############

    /** Called for movement input */
	void MoveAction(const FInputActionValue& Value);

	/** Called for looking input */
	void LookAction(const FInputActionValue& Value);

	void InteractAction();
	
	void FixedTick();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* LookInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* InteractInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* RunInput;



private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class URealisticRunningComponent* RealisticRunningComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake", meta = (AllowPrivateAccess = "true"))
	class UCameraShakeSelectorComponent* CameraShakeSelectorComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 400.0f;
	
	FTimerHandle FixedUpdateHandle;

	//###############
	//###Functions###
	//###############

	bool InteractableReached(FHitResult& OutHitResult);
};
