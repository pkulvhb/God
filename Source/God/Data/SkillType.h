// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "SkillType.generated.h"

USTRUCT(BlueprintType)
struct FSkillType : public FTableRowBase
{
	GENERATED_BODY()
public:
	FSkillType() {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill Info")
	int32 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill Info")
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill Info")
	uint8 Type;
};

