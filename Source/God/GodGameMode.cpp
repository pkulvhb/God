// Copyright Epic Games, Inc. All Rights Reserved.

#include "GodGameMode.h"
#include "GodCharacter.h"
#include "GodPlayerController.h"
#include "Manager/PawnManager.h"
#include "Manager/SkillManager.h"
#include "UObject/ConstructorHelpers.h"

AGodGameMode::AGodGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = AGodPlayerController::StaticClass();
	}
}

void AGodGameMode::BeginPlay()
{
	Super::BeginPlay();
	PawnManager = GetWorld()->SpawnActor<APawnManager>();
	SkillManager = GetWorld()->SpawnActor<ASkillManager>();
}

void AGodGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}