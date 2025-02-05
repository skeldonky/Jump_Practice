// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomGameMode.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

ARandomGameMode::ARandomGameMode()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
