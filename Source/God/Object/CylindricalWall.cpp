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
	//�ӳ�ִ�У��ӳ�2���ִ�У���ִֻ��1��
	//GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, &ACylindricalWall::MonitorPlayer, 1, false, 2);
	//ѭ��ִ�У����ھͿ�ʼִ�У���ÿ��InRate���ִ��һ��
	//GetWorld()->GetTimerManager().SetTimer(MonitorTimer, this, &ACylindricalWall::MonitorPlayer, 1, true, 0);
	//�ӳ�ѭ��ִ�У��ӳ�InFirstDelay���ִ�У���InFirstDelay��֮��ÿ��InRate���ִ��һ��
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

	// �Ƿ���˫�����Խ׶�
	if (bInDoubleClickTest) {
		// ����Ѿ�����˫�����Խ׶Σ���Ƚϴ˿�����һ�������ʱ��ʱ����
		if (NowTime - LastClickTime < DoubleClickTestPadding) {
			//�������㹻С���ʹ���˫���¼����˳�˫�����Խ׶�
			OnLeftDoubleClick();
			bInDoubleClickTest = false;
		}
	}
	else {
		// ���������˫�����Խ׶Σ������˫�����Խ׶�
		bInDoubleClickTest = true;
	}
	// ÿ�����������Ҫ��¼�����ʱ��
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