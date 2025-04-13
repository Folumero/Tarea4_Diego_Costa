#include "VirusComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

UVirusComponent::UVirusComponent()
{
    PrimaryComponentTick.bCanEverTick = false;


}

void UVirusComponent::BeginPlay()
{
    Super::BeginPlay();

    //Empezar con el virus
    GetWorld()->GetTimerManager().SetTimer(InfectionCheckTimer, this, &UVirusComponent::CheckForInfection, CheckFrequency, true);




}

void UVirusComponent::CheckForInfection()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);

    if (ASC)
    {
        DrawDebugSphere(GetWorld(), Owner->GetActorLocation(), InfectionRadius, 12, FColor:: Green, false, 1.0f);

    }

    TArray<AActor*> OverlappingActors;
    UKismetSystemLibrary::SphereOverlapActors(
        GetWorld(),
        Owner->GetActorLocation(),
        InfectionRadius,
        TArray<TEnumAsByte<EObjectTypeQuery>>(),
        AActor::StaticClass(),
        TArray<AActor*>(),
        OverlappingActors


    );

    for (AActor* Actor : OverlappingActors)
    {
        if (Actor && Actor != Owner)
        {
            Infect(Actor);
            
        }
    }

}

void UVirusComponent::Infect(AActor* Target)
{
    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);


    if (ASC && VirusEffect)
    {
        
        FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
        FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(VirusEffect, 1, EffectContext);

        if (EffectSpec.IsValid())
        {
            ASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
            UE_LOG(LogTemp, Warning, TEXT(" %s ha sido infectado"), *Target->GetName());
        }



    }
    if (ASC && !VirusEffect)
    {
        FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
        FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(VirusEffect, 1, EffectContext);

        if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Infected"))))
        {
            VirusEffect = StaticLoadClass(UGameplayEffect::StaticClass(), nullptr, TEXT("/Game/GameplayEffects/Ejercicio3/GE_VirusEffect.GE_VirusEffect_C"));
            UE_LOG(LogTemp, Warning, TEXT("Me han contagio"), *Target->GetName());
        }

    }

}