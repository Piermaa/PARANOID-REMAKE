// Fill out your copyright notice in the Description page of Project Settings.


#include "ParanoidGameInstance.h"


void UParanoidGameInstance::CallEvents(FName Name)
{
	OnParanoidEvent.Broadcast(Name);
}

void UParanoidGameInstance::CallConstEvents(EConstPE ConstEvent)
{
	OnConstantParanoidEvent.Broadcast(ConstEvent);
}

TSet<FName> UParanoidGameInstance::GetKeysFromActor_Implementation()
{
	TSet<FName> KeysSet=TSet<FName>();

	for (auto Key : Keys)
	{
		KeysSet.Add(Key);
	}
	return KeysSet;
}

void UParanoidGameInstance::AddKeyToActor_Implementation(FName NewKey)
{
	if(NewKey.IsValid())
	{
		Keys.Add(NewKey);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Key to Add"));
	}
	
}

void UParanoidGameInstance::ConsumeKeysFromActor_Implementation(const TArray<FName>& KeysToConsume)
{
	for (auto Key : KeysToConsume)
	{
		if(Key.IsValid())
		{
			if(Keys.Contains(Key))
			{
				Keys.Remove(Key);
			}
			else
			{
				FString KeyString=Key.ToString();
				UE_LOG(LogTemp, Error, TEXT("Tried to consume %s, but actor did not have it"), *KeyString);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid Key to Consume"));
		}
	}
}

bool UParanoidGameInstance::ActorHasKeys_Implementation(const TArray<FName>& KeysToCheck)
{
	for (auto Key : KeysToCheck)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checking for: %s"), *Key.ToString());
		
		if(!Key.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid Key to Check"));
			continue;
		}
		if(!Keys.Contains(Key))
		{
			return false;
		}
	}
	
	return true;
}

