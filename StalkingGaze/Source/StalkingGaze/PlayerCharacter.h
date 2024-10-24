
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "KeyHolderActor.h"
#include "PlayerCharacter.generated.h"
class UInputMappingContext;

UCLASS()
class STALKINGGAZE_API APlayerCharacter : public ACharacter
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* CameraComp;
	
	//###############
	//###Functions###
	//###############

    /** Called for movement input */
	void MoveAction(const FInputActionValue& Value);

	/** Called for looking input */
	void LookAction(const FInputActionValue& Value);

	//void InteractAction();
	
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

	// ##################
	// ### COMPONENTS ###
	// ##################
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class URealisticRunningComponent* RealisticRunningComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UFootstepsPlayer* Footsteps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake", meta = (AllowPrivateAccess = "true"))
	class UCameraShakeSelectorComponent* CameraShakeSelectorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keys", meta = (AllowPrivateAccess = "true"))
	class  UKeyHolderComponent* KeyHolderComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	class UItemHolderComponent* ItemHolderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items", meta = (AllowPrivateAccess = "true"))
	class UInteractComponent* InteractComponent;
	
	// ## Other ##
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraSensibility = 1;

	FTimerHandle FixedUpdateHandle;

	// #################
	// ### Functions ###
	// #################

};
