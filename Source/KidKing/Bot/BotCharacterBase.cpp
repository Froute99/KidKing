// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot/BotCharacterBase.h"

#include "AbilitySystemComponent.h"

// Sets default values
ABotCharacterBase::ABotCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilitySystemComponent->Activate();

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));
	//AttributeSetBase = AbilitySystemComponent->GetSet<UCharacterAttributeSetBase>();

	NetUpdateFrequency = 100.0f;

	//GetMesh()->OnComponentHit.AddDynamic(this, &ABotCharacterBase::OnActorHit);
}

UAbilitySystemComponent* ABotCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABotCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//	InitializeStartingValues(PS);
	//AbilitySystemComponent->InitAbilityActorInfo(NewController, this);

	//AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	//HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AKidKingPlayerState::HealthChanged);
	//MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AKidKingPlayerState::MaxHealthChanged);
	//CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &AKidKingPlayerState::CharacterLevelChanged);





	//	AddStartupEffects();
	//if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectApplied)
	//{
	//	return;
	//}

	//FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	//EffectContext.AddSourceObject(this);

	//for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	//{
	//	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);

	//	if (NewHandle.IsValid())
	//	{
	//		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	//	}
	//}

	//AbilitySystemComponent->StartupEffectApplied = true;


	//	AddCharacterAbilities();
	//if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
	//{
	//	return;
	//}

	//for (TSubclassOf<UCharacterGameplayAbility>& StartupAbility : BotAbilities)
	//{
	//	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 0, 0, this));
	//}

	//AbilitySystemComponent->CharacterAbilitiesGiven = true;



}

// Called when the game starts or when spawned
void ABotCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeAttributes();

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->GetSet<UCharacterAttributeSetBase>();

		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &ABotCharacterBase::HandleHealthChanged)
	}
}

// Called every frame
void ABotCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABotCharacterBase::GetHealth() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.f;
}

float ABotCharacterBase::GetMaxHealth() const
{
	if (IsValid(AttributeSetBase))
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

void ABotCharacterBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void ABotCharacterBase::InitializeAttributes()
{
	if (!IsValid(AbilitySystemComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Ability System Component Invalid"), *FString(__FUNCTION__));
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 0, EffectContext);

	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}

}

// Called to bind functionality to input
void ABotCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

