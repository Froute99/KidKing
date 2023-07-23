// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/ProgressBar.h"

void UPlayerWidget::SetHealth(float Value)
{
	if (HealthBar)
	{
		UE_LOG(LogTemp, Log, TEXT("Health Bar Set"));
		HealthBar->SetPercent(Value / MaxHealth);
	}
}

void UPlayerWidget::SetStamina(float Value)
{
	if (StaminaBar)
	{
		UE_LOG(LogTemp, Log, TEXT("Stamina Bar Set"));
		StaminaBar->SetPercent(Value / MaxStamina);
	}
}
