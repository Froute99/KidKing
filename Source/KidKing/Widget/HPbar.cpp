// Fill out your copyright notice in the Description page of Project Settings.


#include "HPbar.h"

void UHPbar::NativeConstruct()
{

}

void UHPbar::set_bar_value_percent(float const value)
{
	HPbar_value->SetPercent(value);
	
}
