// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GodPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GOD_API AGodPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ScreenShot();

	void FastMoveForward(float Value);

	void LookUp(float AxisValue);

	class UCameraComponent* GetCurCameraComponent();

private:
	UPROPERTY()
	class AScreenShotManager* ScreenShotManager;
};
