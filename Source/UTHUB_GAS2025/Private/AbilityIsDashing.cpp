// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityIsDashing.h"

UAbilityIsDashing::UAbilityIsDashing()
{
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsDashing")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsDashing")));
}

void UAbilityIsDashing::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
