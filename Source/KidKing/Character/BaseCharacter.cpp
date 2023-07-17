// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"


#include "CharacterAbilitySystemComponent.h"
#include "CharacterAttributeSetBase.h"
#include "CharacterGameplayAbility.h"


#include "GameFramework/CharacterMovementComponent.h"

#include "PlayerHUD.h"

#include "PlayerWidget.h"

#include "CharacterAnimInstance.h"

#include "Engine/EngineTypes.h"



// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	IsDead = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AKidKingPlayerState* PS = GetPlayerState<AKidKingPlayerState>();
	if (PS)
	{
		InitializeStartingValues(PS);
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

void ABaseCharacter::OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, FHitResult Hit)
{

}

bool ABaseCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 ABaseCharacter::GetAbilityLevel(KidKingAbilityID AbilityID) const
{
	return 1;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ABaseCharacter::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}


	for (int32 i = 0; i < AbilitiesToRemove.Num(); ++i)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = false;

}

// OnActorHit -> Check Hp -> Call Die
void ABaseCharacter::Die()
{
	IsDead = true;
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->StopMovementImmediately();
	//GetCharacterMovement()->Velocity = FVector(0);
	DisableInput(Cast<APlayerController>(GetController()));

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectsTagsToRemove;

		EffectsTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectEremoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);

		OnDyingBP();
	}
}

float ABaseCharacter::GetCharacterLevel() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetLevel();
	}

	return 0.0f;
}

float ABaseCharacter::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.f;
}

float ABaseCharacter::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

float ABaseCharacter::GetStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *FString{__FUNCTION__});
		return AttributeSetBase->GetStamina();
	}

	return 0.0f;
}

float ABaseCharacter::GetMaxStamina() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxStamina();
	}

	return 0.0f;
}

void ABaseCharacter::OnRep_PlayerState()
{
	AKidKingPlayerState* PS = GetPlayerState<AKidKingPlayerState>();
	if (PS)
	{
		InitializeStartingValues(PS);
		BindASCInput();
		InitializeAttributes();
	}
}

void ABaseCharacter::BindASCInput()
{
	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("DemoAbilityID"), static_cast<int32>(KidKingAbilityID::Confirm), static_cast<int32>(KidKingAbilityID::Cancel)));
	}

	ASCInputBound = true;

}

void ABaseCharacter::InitializeStartingValues(AKidKingPlayerState* PS)
{
	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	AttributeSetBase = PS->GetAttributeSetBase();

	if (AttributeSetBase.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("AttributeSetBase is valid"));
	}


	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	InitializeAttributes();


	AttributeSetBase->SetHealth(GetMaxHealth());
	AttributeSetBase->SetStamina(GetMaxHealth());

}

void ABaseCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UCharacterGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;

}

void ABaseCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);

	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}

}

void ABaseCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);

		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->StartupEffectApplied = true;

}

void ABaseCharacter::SetHealth(float Value)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(Value);
	}
}

void ABaseCharacter::InitHealthWidget()
{
	UPlayerWidget* PlayerWidget = Cast<APlayerHUD>((Cast<APlayerController>(GetController())->GetHUD()))->PlayerWidget;
	PlayerWidget->SetHealth(PlayerWidget->MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health bar initialized"));
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APlayerController* PC = CastChecked<APlayerController>(Controller);

	check(EIC && PC);

	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::EnhancedMove);
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::EnhancedLook);
	EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
	//EIC->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ABaseCharacter::DebugAttack);


	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(MappingContext, 0);

	//BindASCInput();
}

void ABaseCharacter::EnhancedMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);


	/*const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MovementVector.Y);
	const FVector Right = GetActorRightVector();
	AddMovementInput(Right, MovementVector.X);*/
}

void ABaseCharacter::EnhancedLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);

}

