////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/TypeId.h>
#include <NsCore/Nullable.h>
#include <NsGui/UIElementData.h>
#include <NsGui/PropertyMetadata.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/UserControl.h>
#include <NsGui/StackPanel.h>
#include <NsGui/Button.h>
#include <NsGui/RadioButton.h>
#include <NsGui/Rectangle.h>
#include <NsGui/Slider.h>
#include <NsGui/Border.h>
#include <NsGui/Canvas.h>
#include <NsGui/Brushes.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/Binding.h>
#include <NsGui/VisualTreeHelper.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/Application.h>
#include <NsApp/Window.h>
#include <NsDrawing/Color.h>
#include <NsDrawing/Thickness.h>
#include <NsDrawing/CornerRadius.h>

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "ColorSelector.xaml.bin.h"
#include "Resources.xaml.bin.h"
#include "WeblySleek_UI_Normal.ttf.bin.h"


using namespace Noesis;
using namespace NoesisApp;


namespace BlendTutorial
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class App final: public Application
{
    NS_IMPLEMENT_INLINE_REFLECTION(App, Application)
    {
        NsMeta<TypeId>("BlendTutorial.App");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ColorSelector final: public UserControl
{
public:
    ColorSelector(): _isUpdatingColor(false), _isUpdatingSliders(false), _r(0), _g(0), _b(0), _a(0)
    {
        InitializeComponent();

        _r = FindName<Slider>("R"); NS_ASSERT(_r);
        _g = FindName<Slider>("G"); NS_ASSERT(_g);
        _b = FindName<Slider>("B"); NS_ASSERT(_b);
        _a = FindName<Slider>("A"); NS_ASSERT(_a);
    }

    SolidColorBrush* GetColor() const
    {
        return GetValue<Ptr<SolidColorBrush>>(ColorProperty);
    }

    void SetColor(SolidColorBrush* color)
    {
        SetValue<Ptr<SolidColorBrush>>(ColorProperty, color);
    }

public:
    static const DependencyProperty* ColorProperty;

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "ColorSelector.xaml");
    }

    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(Slider, ValueChanged, Slider_ValueChanged);
        return false;
    }

    static void OnColorChanged(DependencyObject* d, const DependencyPropertyChangedEventArgs& /*e*/)
    {
        ColorSelector* colorSelector = NsDynamicCast<ColorSelector*>(d);
        if (colorSelector != 0 && !colorSelector->_isUpdatingColor)
        {
            colorSelector->UpdateSliders(colorSelector->GetColor()->GetColor());
        }
    }

    void Slider_ValueChanged(BaseComponent* /*sender*/,
        const RoutedPropertyChangedEventArgs<float>& /*e*/)
    {
        if (!_isUpdatingSliders)
        {
            SolidColorBrush* color = GetColor();
            if (color == 0 || color->IsFrozen())
            {
                _isUpdatingColor = true;
                SetColor(MakePtr<SolidColorBrush>());
                _isUpdatingColor = false;
            }

            UpdateColor(_r->GetValue(), _g->GetValue(), _b->GetValue(), _a->GetValue());
        }
    }

    void UpdateSliders(const Color& color)
    {
        _isUpdatingSliders = true;
        _r->SetValue((float)color.GetRedI());
        _g->SetValue((float)color.GetGreenI());
        _b->SetValue((float)color.GetBlueI());
        _a->SetValue((float)color.GetAlphaI());
        _isUpdatingSliders = false;
    }

    void UpdateColor(float r, float g, float b, float a)
    {
        _isUpdatingColor = true;
        GetColor()->SetColor(Color((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a));
        _isUpdatingColor = false;
    }

private:
    bool _isUpdatingColor;
    bool _isUpdatingSliders;
    Slider* _r;
    Slider* _g;
    Slider* _b;
    Slider* _a;

    NS_IMPLEMENT_INLINE_REFLECTION(ColorSelector, UserControl)
    {
        NsMeta<TypeId>("BlendTutorial.ColorSelector");

        Ptr<UIElementData> data = NsMeta<UIElementData>(TypeOf<SelfClass>());
        data->RegisterProperty<Ptr<SolidColorBrush>>(ColorProperty, "Color",
            PropertyMetadata::Create(Brushes::Transparent()->Clone(),
                &ColorSelector::OnColorChanged));
    }
};

const DependencyProperty* ColorSelector::ColorProperty;

////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow final: public Window
{
public:
    MainWindow()
    {
        InitializeComponent();

        _containerCanvas = FindName<Canvas>("ContainerCanvas"); NS_ASSERT(_containerCanvas != 0);
        _positionLeft = FindName<Slider>("PositionLeft"); NS_ASSERT(_positionLeft != 0);
        _positionTop = FindName<Slider>("PositionTop"); NS_ASSERT(_positionTop != 0);
        _sizeWidth = FindName<Slider>("SizeWidth"); NS_ASSERT(_sizeWidth != 0);
        _sizeHeight = FindName<Slider>("SizeHeight"); NS_ASSERT(_sizeHeight != 0);
        _fillSelected = FindName<RadioButton>("FillSelected"); NS_ASSERT(_fillSelected != 0);
        _colorSelect = FindName<ColorSelector>("ColorSelect"); NS_ASSERT(_colorSelect != 0);

        _selectionBorder = *new Border();
        _selectionBorder->SetBorderBrush(Brushes::Black()->Clone());
        _selectionBorder->GetBorderBrush()->SetOpacity(0.5f);
        _selectionBorder->SetBorderThickness(Thickness(2.0f));
        _selectionBorder->SetCornerRadius(CornerRadius(4.0f));
        _selectionBorder->SetMargin(Thickness(-3.0f, -3.0f, 0.0f, 0.0f));
        _selectionBorder->SetPadding(Thickness(2.0f, 2.0f, 0.0f, 0.0f));
    }

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
    }

    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(Button, Click, AddButton_Click);
        NS_CONNECT_EVENT(Button, Click, RemoveButton_Click);
        NS_CONNECT_EVENT(Border, PreviewMouseLeftButtonDown, ContainerBorder_MouseDown);
        NS_CONNECT_ATTACHED_EVENT(ToggleButton, Checked, RadioButton_Checked);
        return false;
    }

    void AddButton_Click(BaseComponent* /*sender*/, const RoutedEventArgs& /*e*/)
    {
        ClearSelection();

        _selectedRectangle = *new Noesis::Rectangle();
        _selectedRectangle->SetFill(Brushes::Red()->Clone());
        _selectedRectangle->SetStroke(Brushes::Transparent()->Clone());
        _selectedRectangle->SetStrokeThickness(5.0f);

        _positionLeft->SetValue(0.0f);
        _positionTop->SetValue(0.0f);
        _sizeWidth->SetValue(100.0f);
        _sizeHeight->SetValue(100.0f);

        _colorSelect->SetColor(Brushes::Red()->Clone());

        BindSelection();

        _containerCanvas->GetChildren()->Add(_selectedRectangle);

        SetSelection();
    }

    void RemoveButton_Click(BaseComponent* /*sender*/, const RoutedEventArgs& /*e*/)
    {
        if (_selectedRectangle != 0)
        {
            _containerCanvas->GetChildren()->Remove(_selectedRectangle);
            _containerCanvas->GetChildren()->Remove(_selectionBorder);

            _selectedRectangle.Reset();
            _selectionBorder->SetChild(0);
        }
    }

    void ContainerBorder_MouseDown(BaseComponent* /*sender*/, const MouseButtonEventArgs& e)
    {
        Noesis::Rectangle* newSelection = NsDynamicCast<Noesis::Rectangle*>(e.source);
        if (newSelection != _selectedRectangle)
        {
            ClearSelection();

            _selectedRectangle.Reset(newSelection);

            if (_selectedRectangle != 0)
            {
                _positionLeft->SetValue(Canvas::GetLeft(_selectedRectangle));
                _positionTop->SetValue(Canvas::GetTop(_selectedRectangle));
                _sizeWidth->SetValue(_selectedRectangle->GetWidth());
                _sizeHeight->SetValue(_selectedRectangle->GetHeight());
                _colorSelect->SetColor(NsStaticCast<SolidColorBrush*>(
                    _fillSelected->GetIsChecked().GetValue() ?
                    _selectedRectangle->GetFill() : _selectedRectangle->GetStroke()));

                BindSelection();

                SetSelection();
            }
        }

        e.handled = true;
    }

    void RadioButton_Checked(BaseComponent* /*sender*/, const RoutedEventArgs& /*e*/)
    {
        if (_selectedRectangle != 0)
        {
            if (_fillSelected->GetIsChecked().GetValue())
            {
                _selectedRectangle->SetStroke(_colorSelect->GetColor()->Clone());
                _colorSelect->SetColor(NsStaticCast<SolidColorBrush*>(
                    _selectedRectangle->GetFill()));
                Ptr<Binding> binding = *new Binding("Color", _colorSelect);
                _selectedRectangle->SetBinding(Shape::FillProperty, binding);
            }
            else
            {
                _selectedRectangle->SetFill(_colorSelect->GetColor()->Clone());
                _colorSelect->SetColor(NsStaticCast<SolidColorBrush*>(
                    _selectedRectangle->GetStroke()));
                Ptr<Binding> binding = *new Binding("Color", _colorSelect);
                _selectedRectangle->SetBinding(Shape::StrokeProperty, binding);
            }
        }
    }

    void BindSelection()
    {
        Ptr<Binding> binding;

        binding = *new Binding("Value", _positionLeft);
        _selectedRectangle->SetBinding(Canvas::LeftProperty, binding);
        binding = *new Binding("Value", _positionTop);
        _selectedRectangle->SetBinding(Canvas::TopProperty, binding);
        binding = *new Binding("Value", _sizeWidth);
        _selectedRectangle->SetBinding(FrameworkElement::WidthProperty, binding);
        binding = *new Binding("Value", _sizeHeight);
        _selectedRectangle->SetBinding(FrameworkElement::HeightProperty, binding);
        binding = *new Binding("Color", _colorSelect);
        _selectedRectangle->SetBinding(_fillSelected->GetIsChecked().GetValue() ?
            Shape::FillProperty : Shape::StrokeProperty, binding);
    }

    void SetSelection()
    {
        Ptr<Border> selection = *new Border();

        Ptr<Binding> binding;

        binding = *new Binding("Width", _selectedRectangle);
        selection->SetBinding(FrameworkElement::WidthProperty, binding);
        binding = *new Binding("Height", _selectedRectangle);
        selection->SetBinding(FrameworkElement::HeightProperty, binding);

        _selectionBorder->SetChild(selection);

        binding = *new Binding("(Canvas.Left)", _selectedRectangle);
        _selectionBorder->SetBinding(Canvas::LeftProperty, binding);
        binding = *new Binding("(Canvas.Top)", _selectedRectangle);
        _selectionBorder->SetBinding(Canvas::TopProperty, binding);

        _containerCanvas->GetChildren()->Add(_selectionBorder);
    }

    void ClearSelection()
    {
        if (_selectedRectangle != 0)
        {
            Canvas::SetLeft(_selectedRectangle, _positionLeft->GetValue());
            Canvas::SetTop(_selectedRectangle, _positionTop->GetValue());
            _selectedRectangle->SetWidth(_sizeWidth->GetValue());
            _selectedRectangle->SetHeight(_sizeHeight->GetValue());
            if (_fillSelected->GetIsChecked().GetValue())
            {
                _selectedRectangle->SetFill(_colorSelect->GetColor()->Clone());
            }
            else
            {
                _selectedRectangle->SetStroke(_colorSelect->GetColor()->Clone());
            }

            _containerCanvas->GetChildren()->Remove(_selectionBorder);
        }
    }

private:
    Ptr<Noesis::Rectangle> _selectedRectangle;
    Ptr<Border> _selectionBorder;
    Canvas* _containerCanvas;

    Slider* _positionLeft;
    Slider* _positionTop;
    Slider* _sizeWidth;
    Slider* _sizeHeight;

    RadioButton* _fillSelected;

    ColorSelector* _colorSelect;

    NS_IMPLEMENT_INLINE_REFLECTION(MainWindow, Window)
    {
        NsMeta<TypeId>("BlendTutorial.MainWindow");
    }
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        NsRegisterComponent<BlendTutorial::App>();
        NsRegisterComponent<BlendTutorial::MainWindow>();
        NsRegisterComponent<BlendTutorial::ColorSelector>();
    }

    Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml, sizeof(App_xaml) },
            { "MainWindow.xaml", MainWindow_xaml, sizeof(MainWindow_xaml) },
            { "ColorSelector.xaml", ColorSelector_xaml, sizeof(ColorSelector_xaml) },
            { "Resources.xaml", Resources_xaml, sizeof(Resources_xaml) }
        };

        return *new EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
    }

    Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "Fonts", WeblySleek_UI_Normal_ttf, sizeof(WeblySleek_UI_Normal_ttf) }
        };

        return *new EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
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
