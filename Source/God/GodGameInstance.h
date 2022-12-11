// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GodGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GOD_API UGodGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UGodGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Shutdown() override;

	virtual void Init() override;

	virtual void LoadComplete(const float LoadTime, const FString& MapName);
};
