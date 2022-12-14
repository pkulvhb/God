// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GodGameMode.generated.h"

UCLASS(minimalapi)
class AGodGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGodGameMode();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void ScreenShotToImage(const FString& ImagePath, const FVector2D& RangeSize);

	UPROPERTY()
	class APawnManager* PawnManager;

	UPROPERTY()
	class ASkillManager* SkillManager;

	//UPROPERTY()
	//class AScreenShotManager* ScreenShotManager;
};
