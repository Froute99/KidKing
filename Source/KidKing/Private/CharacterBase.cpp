// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

#include "MyAIController.h"
#include "MyAnimInstance.h"
#include "Engine/DamageEvents.h"

#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "HPbar.h"
#include "GameHUD_UI.h"
#include "GameFramework/Actor.h"
//#include "CharacterWidget.h"

#include "MyWeapon.h"
#include "Engine/World.h"

// Sets default values
ACharacterBase::ACharacterBase() : Widget_Component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);
	
	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	myHealth = 0.f;
	myMaxHealth = 100.0f;

	myHealth = myMaxHealth;

	//myHPbar_Text = FString::SanitizeFloat(MyHealth) + "/" + FString::SanitizeFloat(MyMaxHealth);

	//make HPbar on the head
	if (Widget_Component)
	{
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget>widget_class(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HPbar_BP.HPbar_BP_C'"));

		if (widget_class.Succeeded())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, __FUNCTION__);
			Widget_Component->SetWidgetClass(widget_class.Class);

		}
	}

	IsAttacking = false;

}


// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float myHPnum = (myHealth / myMaxHealth);

	auto const uw = Cast<UHPbar>(Widget_Component->GetUserWidgetObject());
	if (uw)
	{
		uw->set_bar_value_percent(myHPnum);
	}

	auto const GameHUD_HPBar = Cast<UGameHUD_UI>(Widget_Component->GetUserWidgetObject());

	if (GameHUD_HPBar)
	{
		GameHUD_HPBar->set_bar_value_percent(myHPnum);
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	MyAnim = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
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

void ACharacterBase::EquipWeapon(AMyWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ACharacterBase::AddWeapon(AMyWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ACharacterBase::SetCurrentWeapon(AMyWeapon* NewWeapon, AMyWeapon* LastWeapon)
{
	AMyWeapon* LocalLastWeapon = NULL;
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
		AMyWeapon* NewWeapon = WRLD->SpawnActor<AMyWeapon>(DefaultInventoryClasses[i], SpawnInfo);
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
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;

	//Capsule 의 Z (Up)를 TraceVec 방향으로 회전 
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
	if (myHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float myGetDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (myGetDamage > 0.f)
	{
		myHealth -= myGetDamage;
	}


	if (myHealth <= 0)
	{
		MyAnim->SetDeadAnim();
		Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(myGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), myHealth));
	}


	return myGetDamage;
}

void ACharacterBase::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage);
	//if (DamageTaken > 0.f)
	//{
	//	ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	//}

}

void ACharacterBase::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{

	myHealth = FMath::Min(0.f, myHealth);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

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

	float DeathAnimDuration = 5.0f;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACharacterBase::DeathAnimationEnd, DeathAnimDuration, false);
}

void ACharacterBase::DeathAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}



float ACharacterBase::get_Health() const
{
	return myHealth;
}

float ACharacterBase::get_maxHealth() const
{
	return myMaxHealth;
}

void ACharacterBase::set_health(float const new_health)
{
	myHealth = new_health;
}




