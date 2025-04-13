// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAttributeEffect.h"
#include "CoreAttributeSet.h"
#include "GameplayEffectExtension.h"


void UGameplayAttributeEffect::ApplyAttributeEffector(const FOnAttributeChangeData& InChangeData)
{
	ReciveApplyAttributeEffector(InChangeData.GEModData->Target.GetOwner(), InChangeData.NewValue, InChangeData.OldValue);

}

