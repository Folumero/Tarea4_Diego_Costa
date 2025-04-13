// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GAS2025Character.h"

#include "GameplayBaseStateTags.h"
#include "GameplayStatesManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GASDataComponent.h"

#include "Materials/Material.h"
#include "CoreAttributeSet.h"
#include "Engine/World.h"
#include "UTHUB_ASC.h"

AUTHUB_GAS2025Character::AUTHUB_GAS2025Character()
{
	ASC = CreateDefaultSubobject<UUTHUB_ASC>(TEXT("ASC"));

	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CoreAttributeSet = CreateDefaultSubobject<UCoreAttributeSet>(TEXT("CoreAttributes"));

	GASDataComponent = CreateDefaultSubobject<UGASDataComponent>(TEXT("GASData"));

}

void AUTHUB_GAS2025Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);


}

void AUTHUB_GAS2025Character::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayStates;
}

void AUTHUB_GAS2025Character::AddTag(const FGameplayTag& InTag)
{
	GameplayStates.AddTag(InTag);
}

void AUTHUB_GAS2025Character::RemoveTag(const FGameplayTag& InTag)
{
	GameplayStates.RemoveTag(InTag);
}

void AUTHUB_GAS2025Character::ApplyGameplyEffect()
{
	if(ASC)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(SampleEffect, 1, EffectContext);

		ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
}


UAbilitySystemComponent* AUTHUB_GAS2025Character::GetAbilitySystemComponent() const
{
	return ASC;
}

void AUTHUB_GAS2025Character::InitializeCharacter()
{
	if (CharacterData)
	{
		TArray<FCharacterAttributes*> OutData;
		CharacterData->GetAllRows(TEXT(""), OutData);

		if (!OutData.IsEmpty())
		{
			FCharacterAttributes** Attr = OutData.FindByPredicate([this](FCharacterAttributes* Row)
			{
				return Row->CharacterClassTag.MatchesTag(CharacterClassTag);
			});
			
			if (Attr) Attributes = *Attr;			
		}
	}
}

void AUTHUB_GAS2025Character::Attack()
{


	if (!Attributes)
	{
		UE_LOG(LogTemp, Error, TEXT("Nullptr"));
		return;
	}

	if (CharacterClassTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("GameplayClasses.Warrior"))))
	{
		Attributes->AttackStrength += 10.0f;
		Attributes->Speed -= 5.0f;           
		UE_LOG(LogTemp, Log, TEXT("Warrior attack: Strength = %f, Speed = %f"), Attributes->AttackStrength, Attributes->Speed);
	}
	else if (CharacterClassTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("GameplayClasses.Mage"))))
	{

		Attributes->AttackStrength += 5.0f;  
		Attributes->Speed += 10.0f;          
		UE_LOG(LogTemp, Log, TEXT("Mage attack: Strength = %f, Speed = %f"), Attributes->AttackStrength, Attributes->Speed);
	}
	else if (CharacterClassTag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("GameplayClasses.Archer"))))
	{
		Attributes->AttackStrength += 15.0f; 
		Attributes->Speed += 5.0f;           
		UE_LOG(LogTemp, Log, TEXT("Archer attack: Strength = %f, Speed = %f"), Attributes->AttackStrength, Attributes->Speed);
	}

}

void AUTHUB_GAS2025Character::BeginPlay()
{
	//if (ensure(ASC))
	//{
	//	//auto& Delegate = ASC->GetGameplayAttributeValueChangeDelegate(UCoreAttributeSet::GetSpeedAttribute());
	//	//Delegate.AddLambda([this](const FOnAttributeChangeData& InChangeData)
	//	//	{
	//	//		GetCharacterMovement()->MaxWalkSpeed = InChangeData.NewValue;
	//	//	});
	//}

	//ASC->GetAttributeSetFrowmOwner<UCoreAttributeSet>()->SetSpeed(400.f);

	Super::BeginPlay();


	SetAttributeCallbacks();

	/*check(CharacterStates)
	GameplayStates.AddTag(CharacterStates->Tag_Alive);*/
	//GameplayStates.AddTag(CharacterClassTag->);

	//InitializeCharacter();
	Attack();

	//ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Infected")));


}

void AUTHUB_GAS2025Character::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AUTHUB_GAS2025Character::Jump()
{
	Super::Jump();

	GameplayStates.RemoveTag(FGameplayStatesManager::Get().Tag_InteractEnabled);
}

void AUTHUB_GAS2025Character::SetAttributeCallbacks()
{
	//for (auto AttributeEffectorsPais: GASDataComponent->AttributeEffectors)
	for (auto [Attribute, EffectorClass] : GASDataComponent->AttributeEffectors)
	{
		auto& Delegate = ASC->GetGameplayAttributeValueChangeDelegate(Attribute);

		UGameplayAttributeEffect* Effector = EffectorClass->GetDefaultObject<UGameplayAttributeEffect>();
		//UObject* Effector = EffectorClass->GetDefaultObject<UObject>();

		Delegate.AddUObject(Effector, &UGameplayAttributeEffect::ApplyAttributeEffector);
	}
}
