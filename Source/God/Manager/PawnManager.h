// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JsonObjectConverter.h"
#include "PawnManager.generated.h"

USTRUCT()
struct FPawnData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		int64 id;

	UPROPERTY()
		int32 type;

	UPROPERTY()
		FString name;

	UPROPERTY()
		float life;

	UPROPERTY()
		FVector pos;

	UPROPERTY()
		TArray<int32> states;

	FString ToString()
	{
		FString OutStr;
		FJsonObjectConverter::UStructToJsonObjectString(*this, OutStr, 0, 0);
		return OutStr;
	}
};

USTRUCT()
struct FPawnDataArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FPawnData> pawns;
	
	FString ToString()
	{
		FString OutStr;
		FJsonObjectConverter::UStructToJsonObjectString(*this, OutStr, 0, 0);
		return OutStr;
	}
};

UCLASS()
class GOD_API APawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	bool InitDataFromJsonFile(const FString& ContentPath);

	bool ComplexInitDataFromJsonFile(const FString& ContentPath);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		FPawnDataArray PawnDataArr;
};
