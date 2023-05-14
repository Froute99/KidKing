// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Engine/DamageEvents.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

#include "PlayerWidget.h"
#include "Blueprint/UserWidget.h"


AMainCharacter::AMainCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	//AIControllerClass = ACustomAIController::StaticClass();
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MaxHp = 100.0f;
	Hp = MaxHp;


	PlayerWidgetClass = nullptr;
	PlayerWidget = nullptr;


}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		Subsystem->AddMappingContext(MovementContext, 0);
	//	}
	//}


	//if (IsLocallyControlled() && PlayerWidget)
	//{
	//	APlayerController* PC = GetController<APlayerController>();
	//	check(PC);
	//	PlayerWidget = CreateWidget<UPlayerWidget>(PC, PlayerWidgetClass);
	//	check(PlayerWidget);
	//	PlayerWidget->AddToPlayerScreen();
	//}

}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}

void AMainCharacter::Die(float Damage, const FDamageEvent& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Super::Die(Damage, DamageEvent, Killer, DamageCauser);


	Hp = FMath::Min(0.f, Hp);		// ?

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearTimer(DeathAnimationTimer);

	PlayAnimMontage(BeDeath_AnimMontage);


	OnCharacterDie();
}

//void AMainCharacter::UpdateHealth(float Delta)
//{
//	Super::UpdateHealth(Delta);
//
//	PlayerWidget->SetHealth(Delta, MaxHp);
//}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMainCharacter::EnhancedMove);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::EnhancedLook);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
	}

	//PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMainCharacter::Attack);

	//BindASCInput();
}

void AMainCharacter::EnhancedMove(const FInputActionValue& Value)
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

void AMainCharacter::EnhancedLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);

}

