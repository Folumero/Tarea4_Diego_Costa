// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayEffect.h"
#include "UObject/Object.h"
#include "GameplayTasksClasses.h"
#include "GameplayAttributeEffect.generated.h"



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UTHUB_GAS2025_API UGameplayAttributeEffect : public UObject
{
	GENERATED_BODY()

public:

	void ApplyAttributeEffector(const FOnAttributeChangeData& InChangeData);

	UFUNCTION(BlueprintImplementableEvent)
	void ReciveApplyAttributeEffector(AActor* InActor, float InValue, float InOldValue);
	
};
