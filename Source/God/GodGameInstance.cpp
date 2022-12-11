// Fill out your copyright notice in the Description page of Project Settings.


#include "GodGameInstance.h"

UGodGameInstance::UGodGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGodGameInstance::Init()
{
	UGameInstance::Init();
}

void UGodGameInstance::Shutdown()
{
	UGameInstance::Shutdown();
}

void UGodGameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);
	UE_LOG(LogTemp, Warning, TEXT("%s LoadComplete"), *MapName);
}



