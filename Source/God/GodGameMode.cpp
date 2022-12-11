// Copyright Epic Games, Inc. All Rights Reserved.

#include "GodGameMode.h"

#include "GameFramework/GameUserSettings.h"

#include "GodCharacter.h"
#include "GodPlayerController.h"
#include "Manager/PawnManager.h"
#include "Manager/SkillManager.h"
#include "Manager/ScreenShotManager.h"
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

	FIntPoint Resolution = GEngine->GetGameUserSettings()->GetScreenResolution();
	UE_LOG(LogTemp, Warning, TEXT("Current Resolution: %d %d"), Resolution.X, Resolution.Y); // 这一行用于打印，可删除
	//UE_LOG(LogTemp, Warning, TEXT("Resolution: %d %d"), Resolution.X, Resolution.Y);
	//GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(2560, 1200));
	//UE_LOG(LogTemp, Warning, TEXT("%s LoadComplete"), *MapName);
}

void AGodGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGodGameMode::ScreenShotToImage(const FString& ImagePath, const FVector2D& RangeSize)
{
	//if (ScreenShotManager)
	//	ScreenShotManager->ScreenShotToImage(ImagePath, RangeSize);
}
