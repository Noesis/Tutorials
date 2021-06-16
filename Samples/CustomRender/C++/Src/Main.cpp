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
#include <NsDrawing/Color.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace Arkanoid
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class Game final: public Noesis::FrameworkElement
{
public:
    Game(): mTicks(HighResTimer::Ticks())
    {
    }

    void OnConnectToView(IView* view)
    {
        ParentClass::OnConnectToView(view);
        view->Rendering() += MakeDelegate(this, &Game::Invalidate);
    }
    void OnDisconnectFromView()
    {
        GetView()->Rendering() -= MakeDelegate(this, &Game::Invalidate);
        ParentClass::OnDisconnectFromView();
    }

    void Invalidate(IView*)
    {
        InvalidateVisual();
    }

    void OnMouseRightButtonDown(const Noesis::MouseButtonEventArgs& e) override
    {
        mSize = Size::Zero();
        ParentClass::OnMouseRightButtonDown(e);
    }

    void OnRender(DrawingContext* context) override
    {
        // Reset when element changes its size
        if (mSize != mRenderSize)
        {
            mSize = mRenderSize;

            mBlockSize.width = mSize.width / 10.0f;
            mBlockSize.height = mSize.height / 12.0f;

            mPadSize.width = mSize.width * 0.125f;
            mPadSize.height = mSize.height * 0.03f;

            mRadius = mSize.width * 0.02f;
            mPos.x = mSize.width / 2.0f;
            mPos.y = mSize.height - mPadSize.height - mRadius;
            mVelX = -2;
            mVelY = -4;

            mPad.l.x = mPos.x - mPadSize.width * 0.5f;
            mPad.l.y = mSize.height - mPadSize.height;
            mPad.h.x = mPad.l.x + mPadSize.width;
            mPad.h.y = mPad.l.y + mPadSize.height;

            if (mPad.color == nullptr)
            {
                mPad.color = MakePtr<SolidColorBrush>(Color::White());
            }

            for (int i = 0; i < 6; ++i)
            {
                for (int j = 0; j < 10; ++j)
                {
                    Block& block = mBlocks[j + i * 10];
                    block.a = 1;
                    block.l = { j * mBlockSize.width, i * mBlockSize.height };
                    block.h = { (j + 1) * mBlockSize.width, (i + 1) * mBlockSize.height };
                    if (block.color == nullptr)
                    {
                        block.color = MakePtr<SolidColorBrush>();
                    }
                    block.color->SetColor(Color::FromPackedRGBA(255 << 24 | rand()));
                }
            }
        }

        // Update blocks
        for (int i = 0; i < 60; ++i)
        {
            Block& block = mBlocks[i];
            if (!block.a) continue;
            if (!block.in(mPos)) continue;
            block.a = false;
            float ol = mPos.x - block.l.x;
            float or = block.h.x - mPos.x;
            float ot = mPos.y - block.l.y;
            float ob = block.h.y - mPos.y;
            float ox = Min(ol, or );
            float oy = Min(ot, ob);
            if (ox < oy)
            {
                mVelX = -mVelX;
            }
            else
            {
                mVelY = -mVelY;
            }
        }

        uint64_t t = HighResTimer::Ticks();
        float dt = (float)HighResTimer::Seconds(t - mTicks);
        mTicks = t;

        // Calculate pad position
        Point mouse = PointFromScreen(GetMouse()->GetPosition());
        mPad.l.x = Min(Max(0.0f, mouse.x - mPadSize.width * 0.5f), mSize.width - mPadSize.width);
        mPad.h.x = mPad.l.x + mPadSize.width;
        if (mPad.in(mPos)) mVelY = -mVelY;

        // Start drawing...

        // background
        context->DrawRectangle(Brushes::Black(), nullptr, Rect(mSize));

        // blocks
        for (int i = 0; i < 60; ++i)
        {
            Block& block = mBlocks[i];
            if (block.a)
            {
                Rect rect(block.l.x, block.l.y, block.h.x, block.h.y);
                context->DrawRectangle(block.color, nullptr, rect);
            }
        }

        // pad
        Rect padRect(mPad.l.x, mPad.l.y, mPad.h.x, mPad.h.y);
        context->DrawRectangle(mPad.color, nullptr, padRect);

        // ball
        context->DrawEllipse(mPad.color, nullptr, mPos, mRadius, mRadius);

        // Update ball position
        mPos.x += mVelX * dt * 30.0f;
        mPos.y += mVelY * dt * 30.0f;
        if (mPos.x < 0.0f || mPos.x > mSize.width) mVelX = -mVelX;
        if (mPos.y < 0.0f) mVelY = -mVelY;
        if (mPos.y > mSize.height) mSize = Size::Zero(); // reset when ball goes down

        mVelX *= 1.00005f;
        mVelY *= 1.0001f;
    }

    uint64_t mTicks;

    struct Block
    {
        Point l;
        Point h;
        Ptr<SolidColorBrush> color;
        bool a;

        bool in(Point p)
        {
            return (p.x > l.x && p.x < h.x) && (p.y > l.y && p.y < h.y);
        }
    };

    Block mBlocks[60];
    Block mPad;
    Size mBlockSize;
    Size mPadSize;
    Size mSize;
    Point mPos;
    float mRadius;
    float mVelX;
    float mVelY;

    NS_IMPLEMENT_INLINE_REFLECTION_(Game, FrameworkElement, "Arkanoid.Game")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public NoesisApp::Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "Arkanoid.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public NoesisApp::Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "Arkanoid.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<Arkanoid::Game>();
        RegisterComponent<Arkanoid::MainWindow>();
        RegisterComponent<Arkanoid::App>();
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
