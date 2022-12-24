// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CylindricalWall.generated.h"

UCLASS()
class GOD_API ACylindricalWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACylindricalWall();

protected:

	virtual void PostActorCreated() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Event when this actor is clicked by the mouse when using the clickable interface. */
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	// Event when this actor has the mouse moved over it with the clickable interface.
	virtual void NotifyActorBeginCursorOver() override;

	// Event when this actor has the mouse moved off of it with the clickable interface.
	virtual void NotifyActorEndCursorOver() override;

	/**
	 *	Event when this actor overlaps another actor, for example a player walking into a trigger.
	 *	For events when objects have a blocking collision, for example a player hitting a wall, see 'Hit' events.
	 *	@note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/**
	 *	Event when an actor no longer overlaps another actor, and they have separated.
	 *	@note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
	 */
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
	// 触发双击事件的时间间隔的临界值
	static const float DoubleClickTestPadding;

	// 记录上一次的点击时刻
	UPROPERTY()
	float LastClickTime = 0;

	// 记录是否在双击测试阶段
	UPROPERTY()
	bool bInDoubleClickTest = false;

	FTimerHandle MonitorTimer;

	UFUNCTION()
	void OnLeftDoubleClick();

	void MonitorPlayer();

};
