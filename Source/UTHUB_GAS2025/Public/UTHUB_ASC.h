// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "UTHUB_ASC.generated.h"

UINTERFACE(NotBlueprintable)
class UGameplayTagCustomInterface : public UGameplayTagAssetInterface
{
	GENERATED_BODY()
};

class IGameplayTagCustomInterface : public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="GameplayTags")
	virtual void AddTag(const FGameplayTag& InTag) = 0;

	UFUNCTION(BlueprintCallable, Category="GameplayTags")
	virtual void RemoveTag(const FGameplayTag& InTag) = 0;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTHUB_GAS2025_API UUTHUB_ASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	UUTHUB_ASC();
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void ApplyEffectFromClass(const TSubclassOf<UGameplayEffect>& EffectClass);
	void RemoveEffect(FActiveGameplayEffectHandle EffectHandle);


protected:
	
	virtual void BeginPlay() override;
	void InitializeAttributesFromEffect();
	

	
public:

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	void AddAbilityFromClass(TSubclassOf<UGameplayAbility>& InGameplayAnilityClass);

	void InitializeAttribute(AActor* InOwnerActor);

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	template<typename AttrSetType>
	AttrSetType* GetAttributeSetFrowmOwner()const;
};

template<typename AttrSetType>
AttrSetType*UUTHUB_ASC::GetAttributeSetFrowmOwner()const{
	if (!GetOwner())
		return nullptr;

	TArray<UObject*>SubObjects;
	GetOwner()->GetDefaultSubobjects(SubObjects);

	UObject** AttrSet = SubObjects.FindByPredicate([](const UObject* Obj) {
		return Obj->IsA(AttrSetType::StaticClass());

		});

	if (!AttrSet) return nullptr;

	return Cast<AttrSetType>(*AttrSet);
}
