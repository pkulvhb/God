// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ScreenShotManager.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/World.h"//GetWord()方法所需要的头文件
#include "TimerManager.h"//定时器所需要的头文件
#include "Modules/ModuleManager.h"//Fmodule头文件
#include "GameFramework/GameUserSettings.h"
//与图片相关的头文件
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "Misc/FileHelper.h"
#include "ImageUtils.h"

// Sets default values
AScreenShotManager::AScreenShotManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));// 创建可附加内容的虚拟根组件。
	CaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent2D"));	// 创建2D相机
	CaptureComponent2D->SetupAttachment(RootComponent);//将CaptureComponent2D绑定到RootComponent组件

	auto RenderTarget2D = NewObject<UTextureRenderTarget2D>(this, TEXT("ScreenShotManager"));
	RenderTarget2D->ClearColor = FLinearColor::Transparent;
	RenderTarget2D->RenderTargetFormat = RTF_RGBA8_SRGB;

	//auto Resolution = GEngine->GetGameUserSettings()->GetScreenResolution();
	//UE_LOG(LogTemp, Warning, TEXT("ResolutionXXX: %d %d"), Resolution.X, Resolution.Y);
	
	RenderTarget2D->InitAutoFormat(1920, 1080);
	RenderTarget2D->UpdateResourceImmediate(true);
	//RenderTarget2D->InitCustomFormat(1920, 1080, PF_FloatRGBA, false);
	CaptureComponent2D->TextureTarget = RenderTarget2D;
}

// Called when the game starts or when spawned
void AScreenShotManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScreenShotManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScreenShotManager::ScreenShotToImage(const FString& InImagePath)
{
	if (CaptureComponent2D && CaptureComponent2D->TextureTarget)
	{
		auto Lab = [=]()
		{
			//获取randerTarget贴图资源  将颜色值全部放入FTextureRenderTargetResource中
			auto Resolution = GEngine->GetGameUserSettings()->GetScreenResolution();
			//UE_LOG(LogTemp, Warning, TEXT("ResolutionXXX: %d %d"), Resolution.X, Resolution.Y);
			//CaptureComponent2D->TextureTarget->ResizeTarget(Resolution.X, Resolution.Y);
			FTextureRenderTargetResource* TextureRenderTargetResource = CaptureComponent2D->TextureTarget->GameThread_GetRenderTargetResource();
			int32 Width = CaptureComponent2D->TextureTarget->SizeX;
			int32 Height = CaptureComponent2D->TextureTarget->SizeY;
			TArray<FColor> OutColor;
			TextureRenderTargetResource->ReadPixels(OutColor);
			WriteColorToImage(InImagePath, OutColor, Width, Height);
		};

		FTimerHandle TimerHandle;//定义一个定时器
		//0.001f后再解析图片写入本地  防止掉帧
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Lab, 0.001f, false, 0);
	}
}

void AScreenShotManager::WriteColorToImage(const FString& InImagePath, TArray<FColor> InColor, int32 InWidth, int32 InHight)
{
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");
    FString	Ext = FPaths::GetExtension(InImagePath).ToLower();
    if (Ext == "jpg" || Ext == "jpeg")
    {
        TSharedPtr<IImageWrapper>ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
        //往本地写，获取颜色数据，获取尺寸，获取长度，高度，格式rgb,8位
        if (ImageWrapper->SetRaw(InColor.GetData(), InColor.GetAllocatedSize(), InWidth, InHight, ERGBFormat::BGRA, 8))
        {
            FFileHelper::SaveArrayToFile(ImageWrapper->GetCompressed(100), *InImagePath);
        }
    }
    else if (Ext == "png")
    {
        TArray<uint8>OutPNG;
        FImageUtils::CompressImageArray(InWidth, InHight, InColor, OutPNG);
        FFileHelper::SaveArrayToFile(OutPNG, *InImagePath);
    }
}


