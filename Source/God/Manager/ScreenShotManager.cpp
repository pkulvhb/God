// Fill out your copyright notice in the Description page of Project Settings.


#include "God/Manager/ScreenShotManager.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/World.h"//GetWord()��������Ҫ��ͷ�ļ�
#include "TimerManager.h"//��ʱ������Ҫ��ͷ�ļ�
#include "Modules/ModuleManager.h"//Fmoduleͷ�ļ�
#include "GameFramework/GameUserSettings.h"
//��ͼƬ��ص�ͷ�ļ�
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "Misc/FileHelper.h"
#include "ImageUtils.h"

// Sets default values
AScreenShotManager::AScreenShotManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));// �����ɸ������ݵ�����������
	CaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent2D"));	// ����2D���
	CaptureComponent2D->SetupAttachment(RootComponent);//��CaptureComponent2D�󶨵�RootComponent���

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
			//��ȡranderTarget��ͼ��Դ  ����ɫֵȫ������FTextureRenderTargetResource��
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

		FTimerHandle TimerHandle;//����һ����ʱ��
		//0.001f���ٽ���ͼƬд�뱾��  ��ֹ��֡
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
        //������д����ȡ��ɫ���ݣ���ȡ�ߴ磬��ȡ���ȣ��߶ȣ���ʽrgb,8λ
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


