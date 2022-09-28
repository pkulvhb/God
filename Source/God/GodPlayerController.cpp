// Fill out your copyright notice in the Description page of Project Settings.


#include "GodPlayerController.h"
#include "GodGameMode.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void AGodPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bEnableClickEvents = true; //打开监听点击事件的开关
	bEnableMouseOverEvents = true; //打开监听鼠标悬停事件的开关
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
	UE_LOG(LogTemp, Warning, TEXT("ScreenShot"));
	//auto GameMode = Cast<AGodGameMode>(UGameplayStatics::GetGameMode(this));
	//UE_LOG(LogTemp, Warning, TEXT("ScreenShot:%s"), *(FPaths::ProjectDir() + "a.jpg"));
	//GameMode->ScreenShotToImage(FPaths::ProjectDir() + "a.jpg", FVector2D(1920, 1080));
}

void AGodPlayerController::FastMoveForward(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("FastMoveForward %f"), Value);
}

void AGodPlayerController::LookUp(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("LookUp %f"), AxisValue);
}
