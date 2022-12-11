// Fill out your copyright notice in the Description page of Project Settings.


#include "CylindricalWall.h"
#include "God/GodCharacter.h"
#include "God/GodGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformStackWalk.h"

const float ACylindricalWall::DoubleClickTestPadding = 0.3f;

//FString GetTraceStack(int32 nDepth = 15)
//{
//	return "";
//	FString RetStrStackInfo = "Stack Info:";
//	TArray<FProgramCounterSymbolInfo> Stack = FPlatformStackWalk::GetStack(0, 15);
//	for (int i = 0; i < Stack.Num(); i++)
//	{
//		RetStrStackInfo += FString("\r\n\t") + FString::Printf(TEXT("FuncName[%s], FileName[%s], LineNumber[%d]"),
//			ANSI_TO_TCHAR(Stack[i].FunctionName), ANSI_TO_TCHAR(Stack[i].Filename), Stack[i].LineNumber);
//	}
//	return RetStrStackInfo;
//}

// Sets default values
ACylindricalWall::ACylindricalWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto Now = FDateTime::Now();
	UE_LOG(LogTemp, Warning, TEXT("ACylindricalWall Time:%d %d %d"), Now.GetMinute(), Now.GetSecond(), Now.GetMillisecond());
	//UE_LOG(LogTemp, Warning, TEXT("ACylindricalWall: %s"), *GetTraceStack());
}

void ACylindricalWall::PostActorCreated()
{
	Super::PostActorCreated();
	auto Now = FDateTime::Now();
	//UE_LOG(LogTemp, Warning, TEXT("PostActorCreated Time:%d %d %d"), Now.GetMinute(), Now.GetSecond(), Now.GetMillisecond());
}

// Called when the game starts or when spawned
void ACylindricalWall::BeginPlay()
{
	Super::BeginPlay();
	auto Now = FDateTime::Now();
	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay Time:%d %d %d"), Now.GetMinute(), Now.GetSecond(), Now.GetMillisecond());
	//延迟执行：延迟2秒后执行，且只执行1次
	//GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, &ACylindricalWall::MonitorPlayer, 1, false, 2);
	//循环执行：现在就开始执行，且每隔InRate秒就执行一次
	//GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, &ACylindricalWall::MonitorPlayer, 1, true, 0);
	//延迟循环执行：延迟InFirstDelay秒后执行，且InFirstDelay秒之后每隔InRate秒就执行一次
	//GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, &ACylindricalWall::MonitorPlayer, 1, true, 2);
}

void ACylindricalWall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(MonitorTimer);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ACylindricalWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACylindricalWall::MonitorPlayer()
{
	auto Now = FDateTime::Now();
	UE_LOG(LogTemp, Warning, TEXT("MonitorPlayer Time:%d %d %d"), Now.GetMinute(), Now.GetSecond(), Now.GetMillisecond());
	//auto Gamemode = Cast<AGodGameMode>(UGameplayStatics::GetGameMode(this));
	auto Player = Cast<AGodCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Player != NULL)
    {
		bool bNotVisible = (GetSquaredDistanceTo(Player) <= 30000);
		SetActorHiddenInGame(bNotVisible);
    }
}


void ACylindricalWall::NotifyActorOnClicked(FKey ButtonPressed) 
{
	Super::NotifyActorOnClicked(ButtonPressed);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Click"));

	double NowTime = FDateTime::Now().GetTimeOfDay().GetTotalSeconds();

	// 是否处于双击测试阶段
	if (bInDoubleClickTest) {
		// 如果已经处于双击测试阶段，则比较此刻与上一次鼠标点击时的时间间隔
		if (NowTime - LastClickTime < DoubleClickTestPadding) {
			//如果间隔足够小，就触发双击事件并退出双击测试阶段
			OnLeftDoubleClick();
			bInDoubleClickTest = false;
		}
	}
	else {
		// 如果不处于双击测试阶段，则进入双击测试阶段
		bInDoubleClickTest = true;
	}
	// 每次鼠标点击，都要记录点击的时刻
	LastClickTime = NowTime;
}

void ACylindricalWall::OnLeftDoubleClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("DoubleClick"));
}


void ACylindricalWall::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("BeginCursorOver"));
}

void ACylindricalWall::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("EndCursorOver"));
}

void ACylindricalWall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	auto Character = Cast<AGodCharacter>(OtherActor);
	if (Character != nullptr)
	{
		SetActorHiddenInGame(true);
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			PC->ClientTravel("/Game/StarterContent/Maps/StarterMap.StarterMap", TRAVEL_Absolute);
			//UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/StarterContent/Maps/StarterMap.StarterMap"), true);
			//Character->SetActorLocation(FVector(100, 0, 0));
		}
		
	}
}

void ACylindricalWall::NotifyActorEndOverlap(AActor* OtherActor)
{
	auto Character = Cast<AGodCharacter>(OtherActor);
	if (Character != nullptr)
	{
		SetActorHiddenInGame(false);
	}
}