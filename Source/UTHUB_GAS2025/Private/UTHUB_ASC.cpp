// Fill out your copyright notice in the Description page of Project Settings.

#include "UTHUB_ASC.h"
#include "CoreAttributeSet.h"
#include "GASDataComponent.h"

#include "NativeGameplayTags.h"

// Sets default values for this component's properties
UUTHUB_ASC::UUTHUB_ASC()
{
	// Set this component to be initialized when the game starts, and to be ticked
	// every frame.  You can turn these features off to improve performance if you
	// don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UUTHUB_ASC::BeginPlay()
{
	Super::BeginPlay();
	//InitializeAttribute(GetOwner());

	InitAbilityActorInfo(GetOwner(), GetOwner());
}

void UUTHUB_ASC::InitializeAttributesFromEffect()
{
	//Init Atributes
		if(UGASDataComponent* DataComponent = GetOwner()-> FindComponentByClass<UGASDataComponent>())
		{
			for(const auto& EffectClass: DataComponent->AttributeInitializers)
			{
				ApplyEffectFromClass(EffectClass);
			}
		}	
}

void UUTHUB_ASC::AddAbilityFromClass(TSubclassOf<UGameplayAbility>& InGameplayAnilityClass)
{
	FGameplayAbilitySpec Spec(InGameplayAnilityClass, 1 , 0);

	GiveAbility(Spec);
}

void UUTHUB_ASC::ApplyEffectFromClass(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle Spec = MakeOutgoingSpec(EffectClass, 1, EffectContext);

	ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
}

void UUTHUB_ASC::RemoveEffect(FActiveGameplayEffectHandle EffectHandle)
{
	if (EffectHandle.IsValid())
	{
		RemoveActiveGameplayEffect(EffectHandle);
	}
}

void UUTHUB_ASC::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	InitializeAttributesFromEffect();

	UGASDataComponent* DataComponent = GetOwner()->FindComponentByClass<UGASDataComponent>();
	if (DataComponent) { AddAbilityFromClass(DataComponent->DefaultAbility); }
	// INIT EFFECT
	// INI ATTRIBS
	// INIT SKILLS
}

void UUTHUB_ASC::InitializeAttribute(AActor* InOwnerActor)
{
	if (UCoreAttributeSet* CoreAttributes = GetAttributeSetFrowmOwner<UCoreAttributeSet>())
	{ 
		if (UGASDataComponent* DataComponent = InOwnerActor->FindComponentByClass<UGASDataComponent>())
		{
			if (DataComponent->DT_CoreStats)
			{
				/*UCoreAttributeSet* CoreSet = const_cast<UCoreAttributeSet*>(GetSet<UCoreAttributeSet>());*/
				//CTrol-K-C
			

				auto InitializeAttrribute = [this, CoreAttributes](const FName& RowName, const FGameplayCoreAttribute& Row)
					{
					

						float NewValue = Row.AttributeBaeValue;

						Row.Attribute.SetNumericValueChecked(NewValue, CoreAttributes);

					};
				DataComponent->DT_CoreStats->ForeachRow<FGameplayCoreAttribute>(TEXT(""), MoveTemp(InitializeAttrribute));
			}
		}
	}
}

// Called every frame
void UUTHUB_ASC::TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
