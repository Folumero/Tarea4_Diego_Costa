#include "CoreAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "GameplayEffectExtension.h"

void UCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute()) 
    {

        if (GetHealth() <= 0) 
        {
            AActor* Owner = GetOwningActor();
            if (Owner)
            {
                UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
                if (ASC)
                {
                    FGameplayTag DeathTag = FGameplayTag::RequestGameplayTag(FName("Character.Dead"));
                    if (!ASC->HasMatchingGameplayTag(DeathTag))
                    {
                        ASC->AddLooseGameplayTag(DeathTag);
                        UE_LOG(LogTemp, Warning, TEXT("Has muerto D;"), *Owner->GetName());
                    }

                }

            }

        }
    }
}

