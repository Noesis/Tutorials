////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsGui/BrushShader.h>
#include <NsGui/UIElementData.h>
#include <NsGui/UIPropertyMetadata.h>
#include <NsRender/RenderContext.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Exo-SemiBold.ttf.bin.h"
#include "fill-blue.png.bin.h"
#include "fill-gold.png.bin.h"

#ifdef HAVE_CUSTOM_SHADERS
#include "Noise.bin.h"
#endif


using namespace Noesis;
using namespace NoesisApp;


namespace BrushShaders
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "BrushShaders.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "BrushShaders.MainWindow")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class NoiseBrush final: public BrushShader
{
public:
    NoiseBrush()
    {
      #ifdef HAVE_CUSTOM_SHADERS
        RenderContext::EnsureShaders(Shaders, "Noise", Noise_bin);
      #endif

        SetConstantBuffer(&mConstants, sizeof(mConstants));

        for (uint32_t i = 0; i < NS_COUNTOF(Shaders.shaders); i++)
        {
            SetPixelShader(Shaders.shaders[i], (BrushShader::Target)i);
        }
    }

public:
    static const DependencyProperty* ColorProperty;
    static const DependencyProperty* ScaleXProperty;
    static const DependencyProperty* ScaleYProperty;
    static const DependencyProperty* TimeProperty;
    static const DependencyProperty* SeedProperty;
    static NoesisApp::BrushShaders Shaders;

private:
    struct Constants
    {
        Color color = Color::White();
        float scaleX = 1.0f;
        float scaleY = 1.0f; 
        float time = 0.0f;
        float seed = 0.0f;
    };

    Constants mConstants;

    NS_IMPLEMENT_INLINE_REFLECTION(NoiseBrush, BrushShader, "BrushShaders.NoiseBrush")
    {
        auto OnColorChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
        {
            NoiseBrush* this_ = (NoiseBrush*)o;
            this_->mConstants.color = args.NewValue<Color>();
            this_->InvalidateConstantBuffer();
        };

        auto OnScaleXChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
        {
            NoiseBrush* this_ = (NoiseBrush*)o;
            this_->mConstants.scaleX = args.NewValue<float>();
            this_->InvalidateConstantBuffer();
        };

        auto OnScaleYChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
        {
            NoiseBrush* this_ = (NoiseBrush*)o;
            this_->mConstants.scaleY = args.NewValue<float>();
            this_->InvalidateConstantBuffer();
        };

        auto OnTimeChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
        {
            NoiseBrush* this_ = (NoiseBrush*)o;
            this_->mConstants.time = args.NewValue<float>();
            this_->InvalidateConstantBuffer();
        };

        auto OnSeedChanged = [](DependencyObject* o, const DependencyPropertyChangedEventArgs& args)
        {
            // Note that dynamic cast is required here because Seed is used as an attached property
            NoiseBrush* this_ = DynamicCast<NoiseBrush*>(o);

            if (this_)
            {
                this_->mConstants.seed = args.NewValue<float>();
                this_->InvalidateConstantBuffer();
            }
        };

        UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
        data->RegisterProperty<Color>(ColorProperty, "Color", UIPropertyMetadata::Create(
            Color::White(), PropertyChangedCallback(OnColorChanged)));
        data->RegisterProperty<float>(ScaleXProperty, "ScaleX", UIPropertyMetadata::Create(
            1.0f, PropertyChangedCallback(OnScaleXChanged)));
        data->RegisterProperty<float>(ScaleYProperty, "ScaleY", UIPropertyMetadata::Create(
            1.0f, PropertyChangedCallback(OnScaleYChanged)));
        data->RegisterProperty<float>(TimeProperty, "Time", UIPropertyMetadata::Create(
            0.0f, PropertyChangedCallback(OnTimeChanged)));
        data->RegisterProperty<float>(SeedProperty, "Seed", UIPropertyMetadata::Create(
            0.0f, PropertyChangedCallback(OnSeedChanged)));
    }
};

const DependencyProperty* NoiseBrush::ColorProperty;
const DependencyProperty* NoiseBrush::ScaleXProperty;
const DependencyProperty* NoiseBrush::ScaleYProperty;
const DependencyProperty* NoiseBrush::TimeProperty;
const DependencyProperty* NoiseBrush::SeedProperty;
NoesisApp::BrushShaders NoiseBrush::Shaders;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<::BrushShaders::App>();
        RegisterComponent<::BrushShaders::MainWindow>();
        RegisterComponent<::BrushShaders::NoiseBrush>();
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

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "", Exo_SemiBold_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] =
        {
            { "fill-blue.png", fill_blue_png },
            { "fill-gold.png", fill_gold_png },
        };

        return *new EmbeddedTextureProvider(textures);
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
