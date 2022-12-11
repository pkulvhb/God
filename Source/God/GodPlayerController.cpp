// Fill out your copyright notice in the Description page of Project Settings.


#include "GodPlayerController.h"
#include "GodCharacter.h"
#include "Manager/ScreenShotManager.h"
   
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GenericPlatform/GenericApplication.h"

// Called when the game starts or when spawned
void AGodPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bEnableClickEvents = true; //打开监听点击事件的开关
	bEnableMouseOverEvents = true; //打开监听鼠标悬停事件的开关

	ScreenShotManager = GetWorld()->SpawnActor<AScreenShotManager>();
	if (GetCurCameraComponent())
		ScreenShotManager->AttachToComponent(GetCurCameraComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void AGodPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction(TEXT("ScreenShot"), EInputEvent::IE_Released, this, &AGodPlayerController::ScreenShot);
	InputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &AGodPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("Fast Move  Forward / Backward"), this, &AGodPlayerController::FastMoveForward);;
}

// Called every frame
void AGodPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bShowMouseCursor = true;
}

void AGodPlayerController::ScreenShot()
{
	if (ScreenShotManager)
		ScreenShotManager->ScreenShotToImage(FPaths::ProjectDir() + "a.PNG");
	//GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	//GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1800, 1200));
	//GEngine->GetGameUserSettings()->ApplySettings(true);
	//FString Command = FString::Printf(TEXT("r.SetRes %dx%dw"), ResX, ResY);
	//ConsoleCommand(Command, true);
	//UKismetSystemLibrary::ExecuteConsoleCommand(this, Command, NULL);
}

void AGodPlayerController::FastMoveForward(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("FastMoveForward %f"), Value);
}

void AGodPlayerController::LookUp(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("LookUp %f"), AxisValue);
}

UCameraComponent* AGodPlayerController::GetCurCameraComponent()
{
	auto CurPawn = Cast<AGodCharacter>(GetPawn());
	return CurPawn!=NULL ? CurPawn->GetFollowCamera() : NULL;
}
