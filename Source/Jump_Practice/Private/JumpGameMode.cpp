// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpGameMode.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

AJumpGameMode::AJumpGameMode()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
