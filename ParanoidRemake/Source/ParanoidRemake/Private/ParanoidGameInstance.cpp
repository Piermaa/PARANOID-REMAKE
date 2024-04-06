// Fill out your copyright notice in the Description page of Project Settings.


#include "ParanoidGameInstance.h"

void UParanoidGameInstance::CallEvents(FName Name)
{
	OnParanoidEvent.Broadcast(Name);
}
