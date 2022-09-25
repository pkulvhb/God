// Fill out your copyright notice in the Description page of Project Settings.


#include "GodPlayerController.h"

// Called when the game starts or when spawned
void AGodPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bEnableClickEvents = true; //打开监听点击事件的开关
	bEnableMouseOverEvents = true; //打开监听鼠标悬停事件的开关
}

// Called every frame
void AGodPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bShowMouseCursor = true;
}