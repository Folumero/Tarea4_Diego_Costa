//#include "LavaPool.h"
//#include "UTHUB_GAS2025/UTHUB_GAS2025Character.h"
//#include "Components/BoxComponent.h"
//#include "AbilitySystemComponent.h"
//
//ALavaPool::ALavaPool()
//{
//    PrimaryActorTick.bCanEverTick = false;
//
//    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
//    RootComponent = CollisionBox;
//    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
//
//    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALavaPool::OnOverlapBegin);
//    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ALavaPool::OnOverlapEnd);
//}
//
//void ALavaPool::BeginPlay()
//{
//    Super::BeginPlay();
//
//}
//
//void ALavaPool::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
//    bool bFromSweep, const FHitResult& SweepResult)
//{
//    AUTHUB_GAS2025Character* Player = Cast<AUTHUB_GAS2025Character>(OtherActor);
//    if (Player)
//    {
//        UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent();
//        if (ASC && LavaDamageEffect)
//        {
//            //Aplicar el GameplayEffect 
//            FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
//            EffectContext.AddSourceObject(this);
//
//            FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(LavaDamageEffect, 1, EffectContext);
//            if (Spec.IsValid())
//            {
//                FActiveGameplayEffectHandle EffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
//                ActiveEffects.Add(Player, EffectHandle);
//
//                UE_LOG(LogTemp, Log, TEXT("Aplicado efecto de lava a %s"), *Player->GetName());
//            }
//        }
//    }
//}
//
//void ALavaPool::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//    AUTHUB_GAS2025Character* Player = Cast<AUTHUB_GAS2025Character>(OtherActor);
//    if (Player)
//    {
//        UAbilitySystemComponent* ASC = Player->GetAbilitySystemComponent();
//        if (ASC && ActiveEffects.Contains(Player))
//        {
//            //Quitar el GameplayEffect 
//            ASC->RemoveActiveGameplayEffect(ActiveEffects[Player]);
//            ActiveEffects.Remove(Player);
//
//            UE_LOG(LogTemp, Log, TEXT("Eliminado efecto de lava de %s"), *Player->GetName());
//        }
//    }
//}
