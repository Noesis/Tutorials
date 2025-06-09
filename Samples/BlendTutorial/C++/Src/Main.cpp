////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/RegisterComponent.h>
#include <NsCore/Nullable.h>
#include <NsGui/UIElementData.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/UserControl.h>
#include <NsGui/UIElementCollection.h>
#include <NsGui/Button.h>
#include <NsGui/RadioButton.h>
#include <NsGui/Rectangle.h>
#include <NsGui/Slider.h>
#include <NsGui/Border.h>
#include <NsGui/Canvas.h>
#include <NsGui/Brushes.h>
#include <NsGui/SolidColorBrush.h>
#include <NsGui/Binding.h>
#include <NsGui/BindingOperations.h>
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
    NS_IMPLEMENT_INLINE_REFLECTION_(App, Application, "BlendTutorial.App")
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ColorSelector final: public UserControl
{
public:
    ColorSelector()
    {
        InitializeComponent();
    }

    SolidColorBrush* GetColor() const
    {
        return GetValue<Noesis::Ptr<SolidColorBrush>>(ColorProperty);
    }

    void SetColor(SolidColorBrush* color)
    {
        SetValue<Noesis::Ptr<SolidColorBrush>>(ColorProperty, color);
    }

public:
    static const DependencyProperty* ColorProperty;

private:
    void InitializeComponent()
    {
        Noesis::GUI::LoadComponent(this, "ColorSelector.xaml");
    }

    bool ConnectField(BaseComponent* object, const char* name) override
    {
        NS_CONNECT_FIELD(_r, "R");
        NS_CONNECT_FIELD(_g, "G");
        NS_CONNECT_FIELD(_b, "B");
        NS_CONNECT_FIELD(_a, "A");

        return false;
    }

    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(Slider, ValueChanged, Slider_ValueChanged);

        return false;
    }

    static void OnColorChanged(DependencyObject* d, const DependencyPropertyChangedEventArgs& /*e*/)
    {
        ColorSelector* colorSelector = DynamicCast<ColorSelector*>(d);
        if (colorSelector != nullptr && !colorSelector->_isUpdatingColor)
        {
            colorSelector->UpdateSliders(colorSelector->GetColor()->GetColor());
        }
    }

    void Slider_ValueChanged(BaseComponent* /*sender*/, const RoutedPropertyChangedEventArgs<float>& /*e*/)
    {
        if (!_isUpdatingSliders)
        {
            SolidColorBrush* color = GetColor();
            if (color == nullptr || color->IsFrozen())
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
        _r->SetValue(color.r * 255.0f);
        _g->SetValue(color.g * 255.0f);
        _b->SetValue(color.b * 255.0f);
        _a->SetValue(color.a * 255.0f);
        _isUpdatingSliders = false;
    }

    void UpdateColor(float r, float g, float b, float a)
    {
        _isUpdatingColor = true;
        GetColor()->SetColor(Color((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a));
        _isUpdatingColor = false;
    }

private:
    bool _isUpdatingColor = false;
    bool _isUpdatingSliders = false;

    Slider* _r = nullptr;
    Slider* _g = nullptr;
    Slider* _b = nullptr;
    Slider* _a = nullptr;

    NS_IMPLEMENT_INLINE_REFLECTION(ColorSelector, UserControl, "BlendTutorial.ColorSelector")
    {
        UIElementData* data = NsMeta<UIElementData>(TypeOf<SelfClass>());
        data->RegisterProperty<Noesis::Ptr<SolidColorBrush>>(ColorProperty, "Color",
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

    bool ConnectField(BaseComponent* object, const char* name) override
    {
        NS_CONNECT_FIELD(_positionLeft, "PositionLeft");
        NS_CONNECT_FIELD(_positionTop, "PositionTop");
        NS_CONNECT_FIELD(_sizeWidth, "SizeWidth");
        NS_CONNECT_FIELD(_sizeHeight, "SizeHeight");
        NS_CONNECT_FIELD(_colorSelect, "ColorSelect");
        NS_CONNECT_FIELD(_containerBorder, "ContainerBorder");
        NS_CONNECT_FIELD(_containerCanvas, "ContainerCanvas");
        NS_CONNECT_FIELD(_fillSelected, "FillSelected");

        return false;
    }

    bool ConnectEvent(BaseComponent* source, const char* event, const char* handler) override
    {
        NS_CONNECT_EVENT(Button, Click, AddButton_Click);
        NS_CONNECT_EVENT(Button, Click, RemoveButton_Click);
        NS_CONNECT_EVENT(Border, PreviewMouseLeftButtonDown, ContainerBorder_MouseDown);
        NS_CONNECT_EVENT(Border, PreviewMouseLeftButtonUp, ContainerBorder_MouseUp);
        NS_CONNECT_EVENT(Border, PreviewMouseMove, ContainerBorder_MouseMove);

        NS_CONNECT_ATTACHED_EVENT(RadioButton, Checked, RadioButton_Checked);

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
        if (_selectedRectangle != nullptr)
        {
            _containerCanvas->GetChildren()->Remove(_selectedRectangle);
            _containerCanvas->GetChildren()->Remove(_selectionBorder);

            _selectedRectangle.Reset();
            _selectionBorder->SetChild(nullptr);
        }
    }

    void ContainerBorder_MouseDown(BaseComponent* /*sender*/, const MouseButtonEventArgs& e)
    {
        Noesis::Rectangle* newSelection = DynamicCast<Noesis::Rectangle*>(e.source);

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
                _colorSelect->SetColor((SolidColorBrush*)(_fillSelected->GetIsChecked().GetValue() ?
                    _selectedRectangle->GetFill() : _selectedRectangle->GetStroke()));

                BindSelection();
                SetSelection();
            }
        }

        if (_selectedRectangle != nullptr)
        {
            _containerBorder->CaptureMouse();
            _isDragging = true;
            _offset = _selectedRectangle->PointFromScreen(e.position);
        }
    }

    void ContainerBorder_MouseUp(BaseComponent* /*sender*/, const MouseButtonEventArgs& /*e*/)
    {
        if (_isDragging)
        {
            _containerBorder->ReleaseMouseCapture();
            _isDragging = false;
        }
    }

    void ContainerBorder_MouseMove(BaseComponent* /*sender*/, const MouseEventArgs& e)
    {
        if (_isDragging && _selectedRectangle != nullptr)
        {
            Noesis::Point max_(
                _containerBorder->GetActualWidth() - _selectedRectangle->GetActualWidth() - 5,
                _containerBorder->GetActualHeight() - _selectedRectangle->GetActualHeight() - 5);
            Noesis::Point p = _containerBorder->PointFromScreen(e.position);
            Canvas::SetLeft(_selectedRectangle, Min(p.x - _offset.x - 2, max_.x));
            Canvas::SetTop(_selectedRectangle, Min(p.y - _offset.y - 2, max_.y));
        }
    }

    void RadioButton_Checked(BaseComponent* /*sender*/, const RoutedEventArgs& /*e*/)
    {
        if (_selectedRectangle != 0)
        {
            if (_fillSelected->GetIsChecked().GetValue())
            {
                _selectedRectangle->SetStroke(_colorSelect->GetColor()->Clone());
                _colorSelect->SetColor((SolidColorBrush*)_selectedRectangle->GetFill());
                Noesis::Ptr<Binding> binding = *new Binding("Color", _colorSelect);
                _selectedRectangle->SetBinding(Shape::FillProperty, binding);
            }
            else
            {
                _selectedRectangle->SetFill(_colorSelect->GetColor()->Clone());
                _colorSelect->SetColor((SolidColorBrush*)_selectedRectangle->GetStroke());
                Noesis::Ptr<Binding> binding = *new Binding("Color", _colorSelect);
                _selectedRectangle->SetBinding(Shape::StrokeProperty, binding);
            }
        }
    }

    void BindSelection()
    {
        {
            Noesis::Ptr<Binding> binding = *new Binding("Value", _positionLeft);
            binding->SetMode(BindingMode_TwoWay);
            _selectedRectangle->SetBinding(Canvas::LeftProperty, binding);
        }
        {
            Noesis::Ptr<Binding> binding = *new Binding("Value", _positionTop);
            binding->SetMode(BindingMode_TwoWay);
            _selectedRectangle->SetBinding(Canvas::TopProperty, binding);
        }
        {
            Noesis::Ptr<Binding> binding = *new Binding("Value", _sizeWidth);
            _selectedRectangle->SetBinding(FrameworkElement::WidthProperty, binding);
        }
        {
            Noesis::Ptr<Binding> binding = *new Binding("Value", _sizeHeight);
            _selectedRectangle->SetBinding(FrameworkElement::HeightProperty, binding); \
        }
        {
            Noesis::Ptr<Binding> binding = *new Binding("Color", _colorSelect);
            _selectedRectangle->SetBinding(_fillSelected->GetIsChecked().GetValue() ?
                Shape::FillProperty : Shape::StrokeProperty, binding);
        }
    }

    void SetSelection()
    {
        Noesis::Ptr<Border> selection = *new Border();

        {
            Noesis::Ptr<Binding> binding = *new Binding("Width", _selectedRectangle);
            selection->SetBinding(FrameworkElement::WidthProperty, binding);
        }

        {
            Noesis::Ptr<Binding> binding = *new Binding("Height", _selectedRectangle);
            selection->SetBinding(FrameworkElement::HeightProperty, binding);
        }

        _selectionBorder->SetChild(selection);

        {
            Noesis::Ptr<Binding> binding = *new Binding("(Canvas.Left)", _selectedRectangle);
            _selectionBorder->SetBinding(Canvas::LeftProperty, binding);
        }
        {
             Noesis::Ptr<Binding> binding = *new Binding("(Canvas.Top)", _selectedRectangle);
            _selectionBorder->SetBinding(Canvas::TopProperty, binding);
        }

        _containerCanvas->GetChildren()->Add(_selectionBorder);
    }

    void ClearSelection()
    {
        if (_selectedRectangle != 0)
        {
            BindingOperations::ClearBinding(_selectedRectangle, Canvas::LeftProperty);
            BindingOperations::ClearBinding(_selectedRectangle, Canvas::TopProperty);
            BindingOperations::ClearBinding(_selectedRectangle, WidthProperty);
            BindingOperations::ClearBinding(_selectedRectangle, HeightProperty);

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
    Noesis::Ptr<Noesis::Rectangle> _selectedRectangle;
    Noesis::Ptr<Border> _selectionBorder;
    bool _isDragging = false;
    Noesis::Point _offset = Noesis::Point(0, 0);

    Slider* _positionLeft = nullptr;
    Slider* _positionTop = nullptr;
    Slider* _sizeWidth = nullptr;
    Slider* _sizeHeight = nullptr;
    ColorSelector* _colorSelect = nullptr;
    Border* _containerBorder = nullptr;
    Canvas* _containerCanvas = nullptr;
    RadioButton* _fillSelected = nullptr;

    NS_IMPLEMENT_INLINE_REFLECTION_(MainWindow, Window, "BlendTutorial.MainWindow")
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
private:
    void RegisterComponents() const override
    {
        RegisterComponent<BlendTutorial::App>();
        RegisterComponent<BlendTutorial::MainWindow>();
        RegisterComponent<BlendTutorial::ColorSelector>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] = 
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "ColorSelector.xaml", ColorSelector_xaml },
            { "Resources.xaml", Resources_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "Fonts", WeblySleek_UI_Normal_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
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
