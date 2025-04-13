// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayAttributeEffect.h"
#include "Components/ActorComponent.h"
#include "InputAbilityMapping.h"
#include "GASDataComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTHUB_GAS2025_API UGASDataComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UGASDataComponent();


	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	UDataTable* DT_CoreStats;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<class UGameplayEffect>> AttributeInitializers;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	TMap<FGameplayAttribute, TSubclassOf<UGameplayAttributeEffect>> AttributeEffectors;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UGameplayAbility> DefaultAbility;

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	UInputAbilityMapping* InputAbilityMapping;
};
