

#include "KeyHolderComponent.h"

UKeyHolderComponent::UKeyHolderComponent()
{

}

bool UKeyHolderComponent::HasKeys(TArray<FName> Keys)
{
	for (auto Key : Keys)
	{
		if(Key==FName())
		{
			continue;
		}
		if(!HeldKeys.Contains(Key))
		{
			return false;
		}
	}

	return true;
}

TSet<FName> UKeyHolderComponent::GetHeldKeys()
{
	return HeldKeys;
}

void UKeyHolderComponent::AddKey(FName NewKey)
{
	HeldKeys.Add(NewKey);
}

void UKeyHolderComponent::ConsumeKeys(TArray<FName> ConsumedKeys)
{
	for (auto Key : ConsumedKeys)
	{
		if(HeldKeys.Contains(Key))
		{
			HeldKeys.Remove(Key);
		}
		else
		{
			FString KeyString=Key.ToString();
			UE_LOG(LogTemp, Error, TEXT("Tried to consume %s, but actor did not have it"), *KeyString);
		}
	}
}

