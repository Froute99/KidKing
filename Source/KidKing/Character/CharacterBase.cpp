// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

#include "CustomAIController.h"
#include "CharacterAnimInstance.h"
#include "Engine/DamageEvents.h"

#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "HPbar.h"
#include "GameHUD_UI.h"
#include "Controller_StartMenu.h"
#include "GameFramework/Actor.h"
//#include "CharacterWidget.h"

#include "KidKingPlayerState.h"

#include "Components/CapsuleComponent.h"
#include "CharacterAbilitySystemComponent.h"
#include "CharacterAttributeSetBase.h"
#include "CharacterGameplayAbility.h"

#include "Weapon.h"
#include "Engine/World.h"

// Sets default values
ACharacterBase::ACharacterBase()
	: Widget_Component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	AIControllerClass = ACustomAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MaxHp = 100.0f;
	Hp = MaxHp;


	//myHPbar_Text = FString::SanitizeFloat(MyHealth) + "/" + FString::SanitizeFloat(MyMaxHealth);

	//make HPbar on the head
	if (Widget_Component)
	{
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HPbar_BP.HPbar_BP_C'"));

		if (widget_class.Succeeded())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, __FUNCTION__);
			Widget_Component->SetWidgetClass(widget_class.Class);

		}
	}

	IsAttacking = false;
	IsBlocking = false;
	Stamina = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));

	BindASCInput();

}

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)),
	Widget_Component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")))
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	bAlwaysRelevant = true;



	//****************************************************************************


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);


	AIControllerClass = ACustomAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MaxHp = 100.0f;
	Hp = MaxHp;


	//myHPbar_Text = FString::SanitizeFloat(MyHealth) + "/" + FString::SanitizeFloat(MyMaxHealth);

	//make HPbar on the head
	if (Widget_Component)
	{
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HPbar_BP.HPbar_BP_C'"));

		if (widget_class.Succeeded())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, __FUNCTION__);
			Widget_Component->SetWidgetClass(widget_class.Class);

		}
	}

	IsAttacking = false;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));


	BindASCInput();

}

bool ACharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 ACharacterBase::GetAbilityLevel(KidKingAbilityID AbilityID) const
{
	return 1;
}

void ACharacterBase::RemoveCharacterAbilities()
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

void ACharacterBase::GSADie()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectsTagsToRemove;

		EffectsTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectEremoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);

		if (DeathMontage)
		{
			PlayAnimMontage(DeathMontage);
		}
		else
		{
			FinishDying();
		}
	}

}

void ACharacterBase::FinishDying()
{
	Destroy();
}

float ACharacterBase::GetCharacterLevel() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetLevel();
	}

	return 0.0f;
}

float ACharacterBase::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("AttributeSetBase is valid"));
		return AttributeSetBase->GetHealth();
	}

	return 0.f;
}

float ACharacterBase::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.f;
}

void ACharacterBase::OnRep_PlayerState()
{
	AKidKingPlayerState* PS = GetPlayerState<AKidKingPlayerState>();
	if (PS)
	{
		InitializeStartingValues(PS);
		BindASCInput();
		InitializeAttributes();
	}
}

void ACharacterBase::BindASCInput()
{
	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("DemoAbilityID"), static_cast<int32>(KidKingAbilityID::Confirm), static_cast<int32>(KidKingAbilityID::Cancel)));
	}

	ASCInputBound = true;
}

void ACharacterBase::InitializeStartingValues(AKidKingPlayerState* PS)
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


	AttributeSetBase->SetHealth(100.0f);
	//SetHealth(100.0f);
	//SetHealth(GetMaxHealth());


	//AddStartupEffects();
	//AddCharacterAbilities();
}


// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HpRate = (Hp / MaxHp);

	auto const uw = Cast<UHPbar>(Widget_Component->GetUserWidgetObject());
	if (uw)
	{
		uw->set_bar_value_percent(HpRate);
	}

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	MyAnim = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (MyAnim)
	{
		MyAnim->OnAttackHitCheck.AddUObject(this, &ACharacterBase::AttackHitCheck);
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MovementContext, 0);
		}
	}

}

void ACharacterBase::AddCharacterAbilities()
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

void ACharacterBase::InitializeAttributes()
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

void ACharacterBase::AddStartupEffects()
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

void ACharacterBase::SetHealth(float Health)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(100.0f);
	}
}

void ACharacterBase::PossessedBy(AController* NewController)
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

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ACharacterBase::EnhancedMove);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterBase::EnhancedLook);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacterBase::Jump);
	}

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ACharacterBase::Attack);

	BindASCInput();
}


void ACharacterBase::EnhancedMove(const FInputActionValue& Value)
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

void ACharacterBase::EnhancedLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);

}

void ACharacterBase::Attack()
{
	if (!IsAttacking)
	{
		MyAnim->PlayAttackMontage_Hero();
		MyAnim->PlayAttackMontage_Bot();
		MyAnim->PlayAttackMontage_Poprika();
		
		OnAttackStart();
	}
}


void ACharacterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnAttackEnd.Broadcast();
}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}



//*******************************************************************
USkeletalMeshComponent* ACharacterBase::GetSpesificPawnMesh() const
{
	return GetMesh();
}

FName ACharacterBase::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void ACharacterBase::EquipWeapon(AWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ACharacterBase::Respawn()
{
	OnRespawn();


	Hp = MaxHp;
	MyAnim->SetDeadAnim(false);


	TeleportTo(SpawnLocation, SpawnRotator, false, false);

}

void ACharacterBase::AddItemToInventory(AItemInterface* Item)
{
	Items.Add(Item);
}

void ACharacterBase::AddWeapon(AWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ACharacterBase::SetCurrentWeapon(AWeapon* NewWeapon, AWeapon* LastWeapon)
{
	AWeapon* LocalLastWeapon = NULL;
	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);

	}
}

void ACharacterBase::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		FActorSpawnParameters SpawnInfo;
		UWorld* WRLD = GetWorld();
		AWeapon* NewWeapon = WRLD->SpawnActor<AWeapon>(DefaultInventoryClasses[i], SpawnInfo);
		NewWeapon->SetOwner(this);
		AddWeapon(NewWeapon);
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
}
//*********************************************************************************
void ACharacterBase::AttackHitCheck()
{
	float AttackRange = 200.0f;
	float AttackRadius = 50.0f;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AMyCharacter::AttackHitCheck()"));

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;

	//Capsule �� Z (Up)�� TraceVec �������� ȸ�� 
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;


	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif

	if (bResult)
	{
		if (HitResult.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit ACtor Name : %s"), *HitResult.GetActor()->GetName());

			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(10.0f, DamageEvent, GetController(), this);
		}
	}

}

float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Hp <= 0.0f)
	{
		return 0.0f;
	}

	const float myGetDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (myGetDamage > 0.f)
	{
		if (IsBlocking == false)
		{
			Hp -= myGetDamage;
			OnHit(myGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), Hp));
		}
		else if (IsBlocking == true)
		{
			Stamina -= 10.0f;
		}
	}


	if (Hp <= 0)
	{
		MyAnim->SetDeadAnim(true);
		if (MyCharacterName == "Player")
		{
			auto World = GetWorld();
			FString CurrentLevel = World->GetMapName();
			AController_StartMenu* con = Cast<AController_StartMenu>(GetOwner());

			if (CurrentLevel == "UEDPIE_0_stage_01")
			{
				con->ShowDieUI();
				Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
			}
			else
			{
				//con->ShowFinalStageDieUI();
				Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
			}

		}
		else
		{
			if (DamageCauser->IsA(AWeapon::StaticClass()))
			{
				Cast<ACharacterBase>(DamageCauser->GetOwner())->Gold += 30;
			}
			else
			{
				Cast<ACharacterBase>(DamageCauser)->Gold += 30;
			}
			
			BotDie(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
		}
	}

	return myGetDamage;
}

void ACharacterBase::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage);
}

void ACharacterBase::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Hp = FMath::Min(0.f, Hp);		// ?

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearTimer(DeathAnimationTimer);

	//PlayAnimMontage(BeDeath_AnimMontage);

	OnCharacterDie();

	//GetWorldTimerManager().ClearAllTimersForObject(this);

	//if (GetCapsuleComponent())
	//{
	//	GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//	GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
	//	GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	//}

	//if (GetCharacterMovement())
	//{
	//	GetCharacterMovement()->StopMovementImmediately();
	//	GetCharacterMovement()->DisableMovement();
	//}


	//if (Controller != NULL)
	//{
	//	Controller->UnPossess();
	//}



	//GetMesh()->SetCollisionProfileName("Ragdoll");
	//GetMesh()->SetSimulatePhysics(true);

	//float DeathAnimDuration = 5.0f;

	//FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(DeathAnimationTimer, this, &ACharacterBase::DeathAnimationEnd, DeathAnimDuration, false);


}

void ACharacterBase::BotDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Hp = FMath::Min(0.f, Hp);		// ?

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);


	GetWorldTimerManager().ClearTimer(DeathAnimationTimer);

	PlayAnimMontage(BeDeath_AnimMontage);
	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}


	if (Controller != NULL)
	{
		Controller->UnPossess();
	}



	//GetMesh()->SetCollisionProfileName("Ragdoll");
	//GetMesh()->SetSimulatePhysics(true);

	GetWorldTimerManager().SetTimer(DeathAnimationTimer, this, &ACharacterBase::DeathAnimationEnd, DeathAnimDuration, false);
}

void ACharacterBase::DeathAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
	MyAnim->SetDeadAnim(false);
}


float ACharacterBase::get_Health() const
{
	return Hp;
}

float ACharacterBase::get_maxHealth() const
{
	return MaxHp;
}

void ACharacterBase::set_health(float const new_health)
{
	Hp = new_health;
}

void ACharacterBase::DebugDecreaseHp()
{
	FDamageEvent DamageEvent;
	TakeDamage(10, DamageEvent, GetController(), this);
}

