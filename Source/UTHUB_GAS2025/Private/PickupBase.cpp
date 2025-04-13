#include "PickupBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"

APickupBase::APickupBase()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnOverlapBegin);
}

void APickupBase::BeginPlay()
{
    Super::BeginPlay();
}

void APickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    // Verificación
    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
    if (ASC && *PickupEffect)
    {
        UE_LOG(LogTemp, Warning, TEXT(" %s tiene un AbilitySystemComponent"), *OtherActor->GetName());

        FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

        if (PickupEffect)
        {
            FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(PickupEffect, 1, EffectContext);

            if (EffectSpec.IsValid())
            {
                ASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
                UE_LOG(LogTemp, Warning, TEXT(" %s ha recibido el efecto del pickup"), *OtherActor->GetName());

                Destroy();
            }

        }

    }

}



