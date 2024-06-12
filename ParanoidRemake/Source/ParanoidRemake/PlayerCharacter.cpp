

#include "PlayerCharacter.h"

#include "CameraShakeSelectorComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "RealisticRunningComponent.h"
#include "FootstepsPlayer.h"
#include "InteractComponent.h"
#include "ItemHolderComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComp->SetupAttachment(SpringArmComponent);
	CameraComp->bUsePawnControlRotation = true;

	RealisticRunningComponent = CreateDefaultSubobject<URealisticRunningComponent>(TEXT("Realistic Runnning"));

	CameraShakeSelectorComponent = CreateDefaultSubobject<UCameraShakeSelectorComponent>(TEXT("Camera Shakes"));
	Footsteps = CreateDefaultSubobject<UFootstepsPlayer>(TEXT("FootstepsPlayer"));
	
	ItemHolderComponent = CreateDefaultSubobject<UItemHolderComponent>(TEXT("ItemHolder"));
	ItemHolderComponent->SetupAttachment(CameraComp);

	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("Interact Component"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	RealisticRunningComponent->Initialize();
	
	CameraShakeSelectorComponent->Initialize
		(GetCharacterMovement(),
		GetController(),
		RealisticRunningComponent
	);
	GetWorld()->GetTimerManager().SetTimer(FixedUpdateHandle, this, &APlayerCharacter::FixedTick, 0.02f, true);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveAction);

		//Looking
		EnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &APlayerCharacter::LookAction);

		//Interacting
		EnhancedInputComponent->BindAction(InteractInput, ETriggerEvent::Started, InteractComponent, &UInteractComponent::Interact);//)&APlayerCharacter::InteractAction);

		//Debugging inputs
		EnhancedInputComponent->BindAction(RunInput, ETriggerEvent::Started, RealisticRunningComponent, &URealisticRunningComponent::RunBeginAction);
		EnhancedInputComponent->BindAction(RunInput, ETriggerEvent::Completed, RealisticRunningComponent, &URealisticRunningComponent::RunEndAction);
	}

}

void APlayerCharacter::MoveAction(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::LookAction(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * CameraSensibility);
		AddControllerPitchInput(LookAxisVector.Y * CameraSensibility);
	}
}

void APlayerCharacter::FixedTick()
{
	RealisticRunningComponent->HandleMovementSpeed();
	CameraShakeSelectorComponent->SelectCameraShake();
	Footsteps->HandleFootsteps();
}

