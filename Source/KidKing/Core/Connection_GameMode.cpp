// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Connection_GameMode.h"
#include "ConnectionState_HUD.h"
#include "Controller_StartMenu.h"

AConnection_GameMode::AConnection_GameMode()
{
	HUDClass = AConnectionState_HUD::StaticClass();
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AController_StartMenu::StaticClass();
}