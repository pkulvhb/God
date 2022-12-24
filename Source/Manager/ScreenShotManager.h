// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScreenShotManager.generated.h"

UCLASS()
class GOD_API AScreenShotManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScreenShotManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ScreenShotToImage(const FString& InImagePath);//将截屏转换为相片
	
	UFUNCTION(BlueprintCallable)
	void WriteColorToImage(const FString& InImagePath, TArray<FColor>InColor, int32 InWidth, int32 InHight);//将颜色数据提取

private:
	UPROPERTY(Category = Default, VisibleAnywhere)
	class USceneCaptureComponent2D* CaptureComponent2D;
};
