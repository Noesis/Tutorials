////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DopesBenchFunctions.h"

#include "Math/UnrealMathUtility.h"

#include "Misc/DateTime.h"
#include "Misc/Timespan.h"

#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

#define FRAND FMath::RandRange(0.0f, 1.0f)

////////////////////////////////////////////////////////////////////////////////////////////////////
const int MaxDopes = 600;

uint64_t gPrevTicks = 0;
int gPrevProcessed = 0;
int gProcessed = 0;
int gAvgNum = 0;
double gAvgSum = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
static void TestBuild(UCanvasPanel* DopesCanvas, UTextBlock* DopesText)
{
    UPackage* Package = GetTransientPackage();
    const FVector2D& Size = DopesCanvas->GetCachedGeometry().GetLocalSize();

    int64 Start = FDateTime::UtcNow().GetTicks();
    int64 Ticks = Start;

    //60hz, 16ms to build the frame
    while (FTimespan(Ticks - Start).GetTotalMilliseconds() < 16.0)
    {
        Ticks = FDateTime::UtcNow().GetTicks();

        UTextBlock* Label = NewObject<UTextBlock>(Package, UTextBlock::StaticClass());
        Label->SetText(FText::FromString("Dope"));
        Label->SetColorAndOpacity(FSlateColor(FLinearColor(FRAND, FRAND, FRAND)));
        Label->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
        Label->SetRenderTransformAngle(-180.0f + FRAND * 360.0f);
        Label->SetRenderTranslation(FVector2D(FRAND * Size.X, FRAND * Size.Y));

        if (gProcessed > MaxDopes)
        {
            DopesCanvas->RemoveChildAt(0);
        }

        DopesCanvas->AddChild(Label);

        gProcessed++;

        double Seconds = FTimespan(Ticks - gPrevTicks).GetTotalSeconds();
        if (Seconds * 1000 > 500)
        {
            double r = (double)(gProcessed - gPrevProcessed) / Seconds;
            gPrevTicks = Ticks;
            gPrevProcessed = gProcessed;

            if (gProcessed > MaxDopes)
            {
                char text[256];
                sprintf_s(text, "%.2f Dopes/s", r);
                DopesText->SetText(FText::FromString(text));

                gAvgSum += r;
                gAvgNum++;
            }
        }
    }

    DopesCanvas->ForceLayoutPrepass();
    GEngine->ForceGarbageCollection(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void TestReuse(UCanvasPanel* DopesCanvas, UTextBlock* DopesText)
{
    UPackage* Package = GetTransientPackage();
    const FVector2D& Size = DopesCanvas->GetCachedGeometry().GetLocalSize();

    int64 Start = FDateTime::UtcNow().GetTicks();
    int64 Ticks = Start;

    //60hz, 16ms to build the frame
    while (FTimespan(Ticks - Start).GetTotalMilliseconds() < 16.0)
    {
        Ticks = FDateTime::UtcNow().GetTicks();

        UTextBlock* Label;
        if (gProcessed < MaxDopes)
        {
            Label = NewObject<UTextBlock>(Package, UTextBlock::StaticClass());
        }
        else
        {
            Label = (UTextBlock*)DopesCanvas->GetChildAt(0);
            DopesCanvas->RemoveChildAt(0);
        }

        Label->SetText(FText::FromString("Dope"));
        Label->SetColorAndOpacity(FSlateColor(FLinearColor(FRAND, FRAND, FRAND)));
        Label->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
        Label->SetRenderTransformAngle(-180.0f + FRAND * 360.0f);
        Label->SetRenderTranslation(FVector2D(FRAND * Size.X, FRAND * Size.Y));

        DopesCanvas->AddChild(Label);

        gProcessed++;

        double Seconds = FTimespan(Ticks - gPrevTicks).GetTotalSeconds();
        if (Seconds * 1000 > 500)
        {
            double r = (double)(gProcessed - gPrevProcessed) / Seconds;
            gPrevTicks = Ticks;
            gPrevProcessed = gProcessed;

            if (gProcessed > MaxDopes)
            {
                char text[256];
                sprintf_s(text, "%.2f Dopes/s", r);
                DopesText->SetText(FText::FromString(text));

                gAvgSum += r;
                gAvgNum++;
            }
        }
    }

    DopesCanvas->ForceLayoutPrepass();
    GEngine->ForceGarbageCollection(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void TestBinding(UCanvasPanel* DopesCanvas, UTextBlock* DopesText)
{
    gAvgSum = 0;
    gAvgNum = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static void TestChange(UCanvasPanel* DopesCanvas, UTextBlock* DopesText)
{
    UPackage* Package = GetTransientPackage();
    const FVector2D& Size = DopesCanvas->GetCachedGeometry().GetLocalSize();

    int64 Start = FDateTime::UtcNow().GetTicks();
    int64 Ticks = Start;

    //60hz, 16ms to build the frame
    while (FTimespan(Ticks - Start).GetTotalMilliseconds() < 16.0)
    {
        Ticks = FDateTime::UtcNow().GetTicks();

        UTextBlock* Label;
        if (gProcessed < MaxDopes)
        {
            Label = NewObject<UTextBlock>(Package, UTextBlock::StaticClass());

            Label->SetText(FText::FromString("Dope"));
            Label->SetColorAndOpacity(FSlateColor(FLinearColor(FRAND, FRAND, FRAND)));
            Label->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
            Label->SetRenderTransformAngle(-180.0f + FRAND * 360.0f);
            Label->SetRenderTranslation(FVector2D(FRAND * Size.X, FRAND * Size.Y));

            DopesCanvas->AddChild(Label);
        }
        else
        {
            const char* texts[] = { "Dope", "dOpe", "doPe", "dopE", "DOpe", "dOPe", "doPE" };
            Label = (UTextBlock*)DopesCanvas->GetChildAt(gProcessed % MaxDopes);
            Label->SetText(FText::FromString(texts[gProcessed % (sizeof(texts) / sizeof(const char*))]));
        }

        gProcessed++;

        double Seconds = FTimespan(Ticks - gPrevTicks).GetTotalSeconds();
        if (Seconds * 1000 > 500)
        {
            double r = (double)(gProcessed - gPrevProcessed) / Seconds;
            gPrevTicks = Ticks;
            gPrevProcessed = gProcessed;

            if (gProcessed > MaxDopes)
            {
                char text[256];
                sprintf_s(text, "%.2f Dopes/s", r);
                DopesText->SetText(FText::FromString(text));

                gAvgSum += r;
                gAvgNum++;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
UDopesBenchFunctions::UDopesBenchFunctions(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void UDopesBenchFunctions::OnTick(UCanvasPanel* DopesCanvas, UTextBlock* DopesText, int RunningTest)
{
    switch (RunningTest)
    {
        case 0: break;
        case 1: TestBuild(DopesCanvas, DopesText); break;
        case 2: TestReuse(DopesCanvas, DopesText); break;
        case 3: TestBinding(DopesCanvas, DopesText); break;
        case 4: TestChange(DopesCanvas, DopesText); break;
        default: break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void UDopesBenchFunctions::StartTest(UCanvasPanel* DopesCanvas, UTextBlock* DopesText)
{
    gPrevTicks = FDateTime::UtcNow().GetTicks();
    gPrevProcessed = 0;
    gProcessed = 0;
    gAvgSum = 0;
    gAvgNum = 0;

    DopesCanvas->ClearChildren();
    DopesText->SetText(FText::FromString("Warming up.."));
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void UDopesBenchFunctions::StopTest(UTextBlock* DopesText)
{
    float avg = float(gAvgSum / (double)gAvgNum);
    char text[256];
    sprintf_s(text, "%.2f Dopes/s (AVG)", avg);
    DopesText->SetText(FText::FromString(text));
}
