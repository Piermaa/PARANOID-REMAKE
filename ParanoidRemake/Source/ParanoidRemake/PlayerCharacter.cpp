

#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "InteractableInterface.h"
#include "DrawDebugHelpers.h"
#include "RealisticRunningComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true;

	RealisticRunningComponent = CreateDefaultSubobject<URealisticRunningComponent>(TEXT("Realistic Runnning"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	RealisticRunningComponent->Initialize();

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
		EnhancedInputComponent->BindAction(InteractInput, ETriggerEvent::Started, this, &APlayerCharacter::InteractAction);

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
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::InteractAction()
{
	FHitResult HitResult;
	if (InteractableReached(HitResult))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		{
			IInteractableInterface::Execute_Interact(HitActor);
		}
	}
}

void APlayerCharacter::FixedTick()
{
	RealisticRunningComponent->HandleMovementSpeed();
}

bool APlayerCharacter::InteractableReached(FHitResult& OutHitResult)
{
	if (CameraComp == nullptr)
	{
		return nullptr;
	}

	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start + CameraComp->GetForwardVector() * InteractionDistance;
	FCollisionQueryParams Params;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 2);
	Params.AddIgnoredActor(this);
	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, Params);
}

