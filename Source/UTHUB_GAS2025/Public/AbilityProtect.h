// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase_Busy.h"
#include "AbilityProtect.generated.h"

/**
 * 
 */
UCLASS()
class UTHUB_GAS2025_API UAbilityProtect : public UAbilityBase_Busy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> ActorToSpawn;
protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:


	UFUNCTION()
	void OnAnimationFinished();

	UPROPERTY(EditAnywhere, Category = "Block", meta = (AllowPrivateAccess = true))
	UAnimMontage* MontageToPlay_;
};
