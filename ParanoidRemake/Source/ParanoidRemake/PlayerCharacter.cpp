

#include "PlayerCharacter.h"

#include "CameraShakeSelectorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "InteractableInterface.h"
#include "DrawDebugHelpers.h"
#include "RealisticRunningComponent.h"
#include "DirectedInteractableInterface.h"
#include "FootstepsPlayer.h"
#include "InteractComponent.h"
#include "ItemHolderComponent.h"
#include "KeyHolderComponent.h"
#include "KeyLockedActorInterface.h"
#include "KeyUnlockerActor.h"
#include "InteractComponent.h"
#include "PickupeableInterface.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->bUsePawnControlRotation = true;

	RealisticRunningComponent = CreateDefaultSubobject<URealisticRunningComponent>(TEXT("Realistic Runnning"));

	CameraShakeSelectorComponent = CreateDefaultSubobject<UCameraShakeSelectorComponent>(TEXT("Camera Shakes"));
	Footsteps = CreateDefaultSubobject<UFootstepsPlayer>(TEXT("FootstepsPlayer"));

	KeyHolderComponent = CreateDefaultSubobject<UKeyHolderComponent>(TEXT("Key Holder"));

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
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
//
// void APlayerCharacter::InteractAction()
// {
// 	FHitResult HitResult;
// 	if (InteractableReached(HitResult))
// 	{
// 		AActor* HitActor = HitResult.GetActor();
// 		UClass* ActorClass= HitActor->GetClass();
//
// 		// Chequeo que no esté lockeado
// 		UE_LOG(LogTemp,Warning, TEXT("Checkeo si esta bloqueado"))
// 		if(ActorClass->ImplementsInterface(UKeyLockedActorInterface::StaticClass()))
// 		{
// 			UE_LOG(LogTemp,Error, TEXT("Esta bloqueado"))
// 			TArray<FName> KeysRequired = TArray<FName>();
// 			IKeyLockedActorInterface::Execute_KeysRequiredToUse(HitActor, KeysRequired);
// 			
// 			if(!Execute_ActorHasKeys(this, KeysRequired))
// 			{
// 				return;
// 			}
// 		}
// 		UE_LOG(LogTemp,Warning, TEXT("Checkeo si es interactuable direccional"))
// 		if(ActorClass->ImplementsInterface(UDirectedInteractableInterface::StaticClass()))
// 		{
// 			IDirectedInteractableInterface::Execute_DirectionDependantInteract(HitActor, CameraComp->GetForwardVector());
// 			UE_LOG(LogTemp,Error, TEXT("Es ii"))
// 		}
// 		UE_LOG(LogTemp,Warning, TEXT("Checkeo si es interactuable"))
// 		// Si es interactuable:
// 		if (ActorClass->ImplementsInterface(UInteractableInterface::StaticClass()))
// 		{
// 			IInteractableInterface::Execute_Interact(HitActor);
//
// 			// Si se puede agarrar
// 			if(ActorClass->ImplementsInterface(UPickupeableInterface::StaticClass()))
// 			{
// 				TArray<UMaterialInterface*> PickupeableMaterials = TArray<UMaterialInterface*>();
// 				UStaticMesh* PickupeableMesh = IPickupeableInterface::Execute_Pickup(HitActor, PickupeableMaterials);
// 				ItemHolderComponent->AddHeldItem(PickupeableMesh, PickupeableMaterials);	
// 			}
// 		}
// 		
// 	}
// }

void APlayerCharacter::FixedTick()
{
	RealisticRunningComponent->HandleMovementSpeed();
	CameraShakeSelectorComponent->SelectCameraShake();
	Footsteps->HandleFootsteps();
}

TSet<FName> APlayerCharacter::GetKeysFromActor_Implementation()
{
	if(KeyHolderComponent!=nullptr)
	{
		return KeyHolderComponent->GetHeldKeys();
	}
	else
	{
		return TSet<FName>();
	}
}

void APlayerCharacter::AddKeyToActor_Implementation(FName NewKey)
{
	if(KeyHolderComponent!=nullptr)
	{
		KeyHolderComponent->AddKey(NewKey);
	}
}

void APlayerCharacter::ConsumeKeysFromActor_Implementation(const TArray<FName>& KeysToConsume)
{
	if(KeyHolderComponent!=nullptr)
	{
		return KeyHolderComponent->ConsumeKeys(KeysToConsume);
	}
}

bool APlayerCharacter::ActorHasKeys_Implementation(const TArray<FName>& KeysToCheck)
{
	if(KeyHolderComponent!=nullptr)
	{
		return KeyHolderComponent->HasKeys(KeysToCheck);
	}
	else
	{
		return false;
	}
}

// bool APlayerCharacter::InteractableReached(FHitResult& OutHitResult)
// {
// 	if (CameraComp == nullptr)
// 	{
// 		return nullptr;
// 	}
//
// 	FVector Start = CameraComp->GetComponentLocation();
// 	FVector End = Start + CameraComp->GetForwardVector() * InteractionDistance;
// 	FCollisionQueryParams Params;
// 	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 2);
// 	Params.AddIgnoredActor(this);
// 	return GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, Params);
// }

