// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/ProgressBar.h"

void UPlayerWidget::SetHealth(float Value, float MaxHealth)
{
	if (HealthBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("In HealthBar"));
		HealthBar->SetPercent(Value / MaxHealth);
	}
}

void UPlayerWidget::SetStamina(float Value, float MaxStamina)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Value / MaxStamina);
	}
}
