// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/BotAttributeSetBase.h"
#include "Net/UnrealNetwork.h"

void UBotAttributeSetBase::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBotAttributeSetBase, Level, OldLevel);
}

void UBotAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBotAttributeSetBase, Health, OldHealth);
}

void UBotAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBotAttributeSetBase, MaxHealth, OldMaxHealth);
}

void UBotAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBotAttributeSetBase, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBotAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBotAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
}


