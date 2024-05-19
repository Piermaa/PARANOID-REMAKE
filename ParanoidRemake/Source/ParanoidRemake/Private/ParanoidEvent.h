// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParanoidEventInterface.h"
#include "GameFramework/Actor.h"
#include "ParanoidEvent.generated.h"

UCLASS()
class AParanoidEvent : public AActor, public IParanoidEventInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParanoidEvent();

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debugging")
	bool ShowDebugElements;

	UPROPERTY(EditDefaultsOnly="Debugging")
	class UBillboardComponent* BillboardComponent;
	
	UPROPERTY(EditDefaultsOnly="Debugging")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Debugging")
	class UTextRenderComponent* TextRenderComponent;
	
	UPROPERTY(EditAnywhere, Category = "Paranoid Event")
	FName ParanoidEventName;
	
	UPROPERTY(EditAnywhere, Category = "Paranoid Event")
	bool InvokeOnce;
	
	bool Invoked=false;

	UFUNCTION(BlueprintCallable, CallInEditor, BlueprintNativeEvent, Category="Debugging")
	void UpdateDebugSymbols();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Paranoid Event") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void TryInvokeEvent();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Paranoid Event") //BNE PERMITE QUE PUEDA SER LLAMADO E IMPLEMENTADO
	void InvokeEvent();

	UFUNCTION(Blueprintable)
	void InvokeEventByName(FName EventName);

};
