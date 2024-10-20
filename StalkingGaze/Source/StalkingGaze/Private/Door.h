// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParanoidEventDispatcher.h"
#include "GameFramework/Actor.h"
#include "StalkingGaze/DirectedInteractableInterface.h"
#include "Door.generated.h"

UCLASS()
class ADoor : public AParanoidEventDispatcher, public IDirectedInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	virtual void BeginPlay() override;

public:	
	//########
	//##Vars##
	//########
	UPROPERTY(EditAnywhere, Category = "Door | Mesh")
	class UStaticMeshComponent* Door;

	UPROPERTY()
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, Category = "Door | Mesh")
	class UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere, Category= "Door | Animation")
	float SwingSpeed=80;

	UPROPERTY(EditAnywhere, Category= "Door | Animation")
	bool bUseOpenAnimation = true;
	
	//#########
	//##Funcs##
	//#########
	virtual void Tick(float DeltaTime) override;

	virtual void DirectionDependantInteract_Implementation(FVector Forward) override;

	UFUNCTION()
	void ToggleDoor(FVector ForwardVector);
	
	UFUNCTION()
	void OpenDoor(float Dt);

	UFUNCTION()
	void CloseDoor(float Dt);
	
	UFUNCTION()
	void SetYaw(float Yaw) const;


private:
	UPROPERTY(EditAnywhere, Category = "Door | Mesh", meta = (AllowPrivateAccess = "true"))
	bool bInvertedMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bOpening = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bClosing = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bIsClosed = true;

	float DotP;
	float MaxDegree; //si se abre 90 o -90 grados
	float AddRotation;
	float PosNeg; // Determinar si es positivo o no dependiendo de si lo miramos
	float DoorCurrentRotation;

	float StartingRotation;
};
