// Fill out your copyright notice in the Description page of Project Settings.


#include "GodPlayerController.h"

// Called when the game starts or when spawned
void AGodPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bEnableClickEvents = true; //�򿪼�������¼��Ŀ���
	bEnableMouseOverEvents = true; //�򿪼��������ͣ�¼��Ŀ���
}

// Called every frame
void AGodPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bShowMouseCursor = true;
}