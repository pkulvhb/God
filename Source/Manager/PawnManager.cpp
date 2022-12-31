// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnManager.h"
#include "MacroDefine.h"

// Sets default values
APawnManager::APawnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APawnManager::BeginPlay()
{
	Super::BeginPlay();
#if TEST_JSON_PARSE
	FString FileName = "data/pawns.json";
	InitDataFromJsonFile(FileName);
#endif
}

// Called every frame
void APawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APawnManager::InitDataFromJsonFile(const FString& ContentPath)
{
	PawnDataArr.pawns.Empty();
	FString AbsPath = FPaths::ProjectContentDir() + ContentPath;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*AbsPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s not exist"), *AbsPath);
		return false;
	}

	FString FileStr;
	if (FFileHelper::LoadFileToString(FileStr, *(AbsPath)))
	{

		// 简洁的实现方法
		{
			FPawnDataArray ArrayData;
			if (!FJsonObjectConverter::JsonObjectStringToUStruct(FileStr, &ArrayData, 0, 0))
			{
				UE_LOG(LogTemp, Error, TEXT("FPawnData Convert Fail"));
				return false;
			}
			for (auto& PawnData : ArrayData.pawns)
			{
				UE_LOG(LogTemp, Warning, TEXT(" \nFPawnData: \n %s"), *PawnData.ToString());
			}
		}

		TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(FileStr);
		TSharedPtr<FJsonObject> Root;
	}

	return true;
}

bool APawnManager::ComplexInitDataFromJsonFile(const FString& ContentPath)
{
	PawnDataArr.pawns.Empty();
	FString AbsPath = FPaths::ProjectContentDir() + ContentPath;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*AbsPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s not exist"), *AbsPath);
		return false;
	}

	FString FileStr;
	if (FFileHelper::LoadFileToString(FileStr, *(AbsPath)))
	{
		TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(FileStr);
		TSharedPtr<FJsonObject> Root;

		if (FJsonSerializer::Deserialize(Reader, Root))
		{
			if (Root->HasField(TEXT("pawns")))
			{
				const TArray<TSharedPtr<FJsonValue>> Arr = Root->GetArrayField(TEXT("pawns"));
				for (const auto JsonPtr : Arr) {
					auto Obj = JsonPtr->AsObject();

					FPawnData Data;
					if (Obj->HasField(TEXT("id")))
						Data.id = Obj->GetNumberField(TEXT("id"));
					if (Obj->HasField(TEXT("type")))
						Data.type = Obj->GetNumberField(TEXT("type"));
					if (Obj->HasField(TEXT("name")))
						Data.name = Obj->GetStringField(TEXT("name"));
					if (Obj->HasField(TEXT("life")))
						Data.life = Obj->GetNumberField(TEXT("life"));

					if (Obj->HasField(TEXT("pos"))) {
						auto Pos = Obj->GetObjectField(TEXT("pos"));
						if (Pos->HasField(TEXT("X")))
							Data.pos.X = Pos->GetNumberField(TEXT("X"));
						if (Pos->HasField(TEXT("Y")))
							Data.pos.Y = Pos->GetNumberField(TEXT("Y"));
						if (Pos->HasField(TEXT("Z")))
							Data.pos.Z = Pos->GetNumberField(TEXT("Z"));
					}

					if (Obj->HasField(TEXT("states"))) {
						auto States = Obj->GetArrayField(TEXT("states"));
						for (int i = 0; i < States.Num(); i++)
						{
							Data.states.Add(States[i]->AsNumber());
						}
					}

					UE_LOG(LogTemp, Warning, TEXT(" \nFPawnData: \n %s"), *Data.ToString());
					PawnDataArr.pawns.Add(Data);
				}
			}
		}
	}

	return true;
}
