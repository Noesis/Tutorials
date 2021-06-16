////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/HighResTimer.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/Brushes.h>
#include <NsGui/IView.h>
#include <NsGui/Mouse.h>
#include <NsGui/DrawingContext.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"


using namespace Noesis;
using namespace NoesisApp;


static const float Width = 800.0f;
static const float Height = 600.0f;
static const float PadWidth = 85.0f;
static const float PadHeight = 22.0f;
static const float BlockWidth = Width / 13.0f;
static const float BlockHeight = 30.0f;


namespace CustomRender
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class Game final: public Noesis::FrameworkElement
{
public:
    Game()
    {
        Reset();
    }

    void OnConnectToView(IView* view) override
    {
        ParentClass::OnConnectToView(view);
        view->Rendering() += MakeDelegate(this, &Game::Invalidate);
    }
    void OnDisconnectFromView() override
    {
        GetView()->Rendering() -= MakeDelegate(this, &Game::Invalidate);
        ParentClass::OnDisconnectFromView();
    }

    void Invalidate(IView*)
    {
        InvalidateVisual();
    }

    void Reset()
    {
        mLastTime = HighResTimer::Ticks();

        memset(mBlocks, 0, sizeof(mBlocks));

        mPosX = Width / 2.0f;
        mPosY = Height - PadHeight - 50.0f;
        mVelX = -2.0f;
        mVelY = -4.0f;
    }

    void OnRender(DrawingContext* context) override
    {
        uint64_t t = HighResTimer::Ticks();
        float dt = (float)HighResTimer::Seconds(t - mLastTime);
        mLastTime = t;

        // Draw background
        context->DrawRectangle(Brushes::Black(), nullptr, Rect(0, 0, Width, Height));

        // Draw pad
        {
            Point mouse = PointFromScreen(GetMouse()->GetPosition());
            float x = Min(Max(mouse.x, PadWidth * 0.5f), Width - PadWidth * 0.5f);

            float x0 = x - PadWidth * 0.5f;
            float x1 = x0 + PadWidth;
            float y0 = 550.0f - PadHeight * 0.5f;
            float y1 = y0 + PadHeight;

            if (mPosX >= x0 && mPosX <= x1 && mPosY >= y0 && mPosY <= y1)
            {
                if (mVelY > 0.0f) mVelY = -mVelY;

                float vScale = (mPosX - x) / (PadWidth * 0.5f);
                mVelX += vScale * 2.0f;
            }

            context->DrawRectangle(Brushes::Silver(), nullptr, Rect(x0 + 18.0f, y0, x1 - 18.0f, y0 + 4.0f));
            context->DrawRectangle(Brushes::Lavender(), nullptr, Rect(x0 + 18.0f, y0 + 4.0f, x1 - 18.0f, y0 + 8.0f));
            context->DrawRectangle(Brushes::Silver(), nullptr, Rect(x0 + 18.0f, y0 + 8.0f, x1 - 18.0f, y0 + 15.0f));
            context->DrawRectangle(Brushes::SlateGray(), nullptr, Rect(x0 + 18.0f, y0 + 15.0f, x1 - 18.0f, y1));

            context->DrawRectangle(Brushes::Gold(), nullptr, Rect(x1 - 16.0f, y0, x1, y0 + 4.0f));
            context->DrawRectangle(Brushes::Khaki(), nullptr, Rect(x1 - 16.0f, y0 + 4.0f, x1, y0 + 8.0f));
            context->DrawRectangle(Brushes::Gold(), nullptr, Rect(x1 - 16.0f, y0 + 8.0f, x1, y0 + 15.0f));
            context->DrawRectangle(Brushes::Goldenrod(), nullptr, Rect(x1 - 16.0f, y0 + 15.0f, x1, y1));

            context->DrawRectangle(Brushes::Gold(), nullptr, Rect(x0, y0, x0 + 16.0f, y0 + 4.0f));
            context->DrawRectangle(Brushes::Khaki(), nullptr, Rect(x0, y0 + 4.0f, x0 + 16.0f, y0 + 8.0f));
            context->DrawRectangle(Brushes::Gold(), nullptr, Rect(x0, y0 + 8.0f, x0 + 16.0f, y0 + 15.0f));
            context->DrawRectangle(Brushes::Goldenrod(), nullptr, Rect(x0, y0 + 15.0f, x0 + 16.0f, y1));
        }

        // Draw blocks
        {
            static Brush* brushes0[] = { Brushes::Red(), Brushes::Gold(), Brushes::MediumBlue(), Brushes::Magenta(), Brushes::Lime() };
            static Brush* brushes1[] = { Brushes::DarkRed(), Brushes::Goldenrod(), Brushes::Navy(), Brushes::DarkMagenta(), Brushes::LimeGreen() };

            for (uint32_t i = 0; i < 5; i++)
            {
                for (uint32_t j = 0; j < 13; j++)
                {
                    if (mBlocks[i][j])
                    {
                        continue;
                    }

                    float x0 = j * BlockWidth;
                    float x1 = x0 + BlockWidth;
                    float y0 = i * BlockHeight + 100.0f;
                    float y1 = y0 + BlockHeight;

                    if (mPosX >= x0 && mPosX <= x1 && mPosY >= y0 && mPosY <= y1)
                    {
                        mBlocks[i][j] = true;

                        float dx0 = mPosX - x0;
                        float dx1 = x1 - mPosX;
                        float dy0 = mPosY - y0;
                        float dy1 = y1 - mPosY;

                        if (Min(dx0, dx1) < Min(dy0, dy1))
                        {
                            mVelX = -mVelX;
                        }
                        else
                        {
                            mVelY = -mVelY;
                        }
                    }

                    context->DrawRectangle(brushes0[i], nullptr, Rect(x0 + 2.0f, y0 + 2.0f, x1 - 2.0f, y1 - 2.0f));
                    context->DrawRectangle(brushes1[i], nullptr, Rect(x0 + 5.0f, y0 + 25.0f, x1 - 2.0f, y1 - 2.0f));
                    context->DrawRectangle(brushes1[i], nullptr, Rect(x0 + 57.0f, y0 + 5.0f, x1 - 2.0f, y1 - 2.0f));
                }
            }
        }

        // Draw ball
        {
            mPosX += mVelX * dt * 60.0f;
            mPosY += mVelY * dt * 60.0f;
            if (mPosX < 0.0f || mPosX > Width) mVelX = -mVelX;
            if (mPosY < 0.0f) mVelY = -mVelY;
            if (mPosY > Height) Reset();

            mVelX *= 1.00005f;
            mVelY *= 1.0001f;

            float x0 = mPosX - 7.0f;
            float x1 = mPosX + 7.0f;
            float y0 = mPosY - 7.0f;
            float y1 = mPosY + 7.0f;

            context->DrawRectangle(Brushes::LightSkyBlue(), nullptr, Rect(x0 + 2.0f, y0 + 2.0f, x1 - 2.0f, y1 - 2.0f));
            context->DrawRectangle(Brushes::Aqua(), nullptr, Rect(x0 - 2.0f, y0 + 2.0f, x0 + 2.0f, y1 - 2.0f));
            context->DrawRectangle(Brushes::Aqua(), nullptr, Rect(x1 - 2.0f, y0 + 2.0f, x1 + 2.0f, y1 - 2.0f));
            context->DrawRectangle(Brushes::Aqua(), nullptr, Rect(x0 + 2.0f, y0 - 2.0f, x1 - 2.0f, y0 + 2.0f));
            context->DrawRectangle(Brushes::Aqua(), nullptr, Rect(x0 + 2.0f, y1 - 2.0f, x1 - 2.0f, y1 + 2.0f));
        }
    }

    bool mBlocks[5][13];

    float mPosX;
    float mPosY;
    float mVelX;
    float mVelY;

    uint64_t mLastTime;

    NS_IMPLEMENT_INLINE_REFLECTION_(Game, FrameworkElement, "CustomRender.Game")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public NoesisApp::Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "CustomRender.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public NoesisApp::Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "CustomRender.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<CustomRender::Game>();
        RegisterComponent<CustomRender::MainWindow>();
        RegisterComponent<CustomRender::App>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
int NsMain(int argc, char **argv)
{
    AppLauncher launcher;
    launcher.SetArguments(argc, argv);
    launcher.SetApplicationFile("App.xaml");
    return launcher.Run();
}
