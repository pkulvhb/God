// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SkillManager.h"
#include "Data/SkillType.h"
#include "MacroDefine.h"

// Sets default values
ASkillManager::ASkillManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASkillManager::BeginPlay()
{
	Super::BeginPlay();
#if TEST_DATATABLE
	UDataTable* SkillTypeTable = LoadObject<UDataTable>(NULL, TEXT("DataTable'/Game/Data/SkillTypeTable.SkillTypeTable'"));
	if (!SkillTypeTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Load SkillTypeTable Fail"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Display the use of GetRowMap:"));
	for (auto it : SkillTypeTable->GetRowMap())
	{
		FSkillType* Row = (FSkillType*)it.Value;
		if (Row)
		{
			UE_LOG(LogTemp, Warning, TEXT("SkillType: %s %d %s %d"), *it.Key.ToString(), Row->ID, *Row->Name.ToString(), Row->Type);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Display the use of GetAllRows:"));
	TArray<FSkillType*> SkillTypeArr;
	SkillTypeTable->GetAllRows("", SkillTypeArr);
	for (auto SkillType : SkillTypeArr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillType: %d %s %d"), SkillType->ID, *SkillType->Name.ToString(), SkillType->Type);
	}

	UE_LOG(LogTemp, Warning, TEXT("Display the use of FindRow:"));
	auto RowNames = SkillTypeTable->GetRowNames();
	for (auto RowName : RowNames)
	{
		FSkillType* SkillType = SkillTypeTable->FindRow<FSkillType>(RowName, TEXT("IconReference"));
		UE_LOG(LogTemp, Warning, TEXT("SkillType: %d %s %d"), SkillType->ID, *SkillType->Name.ToString(), SkillType->Type);
	}
#endif
}

// Called every frame
void ASkillManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

