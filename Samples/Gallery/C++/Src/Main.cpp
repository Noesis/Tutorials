////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Noesis.h>
#include <NsCore/RegisterComponent.h>
#include <NsApp/ApplicationLauncher.h>
#include <NsApp/EntryPoint.h>
#include <NsApp/EmbeddedXamlProvider.h>
#include <NsApp/EmbeddedFontProvider.h>
#include <NsApp/EmbeddedTextureProvider.h>

#include "App.xaml.h"
#include "MainWindow.xaml.h"

#include "App.xaml.bin.h"
#include "MainWindow.xaml.bin.h"
#include "Resources.xaml.bin.h"

#include "Button.xaml.bin.h"
#include "RepeatButton.xaml.bin.h"
#include "ToggleButton.xaml.bin.h"
#include "CheckBox.xaml.bin.h"
#include "RadioButton.xaml.bin.h"
#include "Slider.xaml.bin.h"
#include "TextBlock.xaml.bin.h"
#include "TextBox.xaml.bin.h"
#include "PasswordBox.xaml.bin.h"
#include "Hyperlink.xaml.bin.h"
#include "ItemsControl.xaml.bin.h"
#include "ComboBox.xaml.bin.h"
#include "ListBox.xaml.bin.h"
#include "ListView.xaml.bin.h"
#include "TreeView.xaml.bin.h"
#include "TabControl.xaml.bin.h"
#include "Canvas.xaml.bin.h"
#include "StackPanel.xaml.bin.h"
#include "WrapPanel.xaml.bin.h"
#include "DockPanel.xaml.bin.h"
#include "Grid.xaml.bin.h"
#include "UniformGrid.xaml.bin.h"
#include "GroupBox.xaml.bin.h"
#include "Expander.xaml.bin.h"
#include "ScrollViewer.xaml.bin.h"
#include "Menu.xaml.bin.h"
#include "ContextMenu.xaml.bin.h"
#include "ToolBar.xaml.bin.h"
#include "StatusBar.xaml.bin.h"
#include "ProgressBar.xaml.bin.h"
#include "ToolTip.xaml.bin.h"
#include "Brushes.xaml.bin.h"
#include "Image.xaml.bin.h"
#include "Effects.xaml.bin.h"
#include "Animation.xaml.bin.h"

#include "Muli-Regular.ttf.bin.h"
#include "Muli-Bold.ttf.bin.h"
#include "Muli-Italic.ttf.bin.h"
#include "Caladea-Regular.ttf.bin.h"
#include "CourierPrime-Regular.ttf.bin.h"
#include "WidgetIcons.ttf.bin.h"

#include "file.png.bin.h"
#include "folder-closed.png.bin.h"
#include "folder-open.png.bin.h"
#include "recycling-bin.png.bin.h"
#include "floppy-disk.png.bin.h"
#include "search.png.bin.h"
#include "Nature.png.bin.h"


using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
class AppLauncher final: public ApplicationLauncher
{
public:
    void RegisterComponents() const override
    {
        RegisterComponent<Gallery::App>();
        RegisterComponent<Gallery::MainWindow>();
    }

    Noesis::Ptr<XamlProvider> GetXamlProvider() const override
    {
        EmbeddedXaml xamls[] =
        {
            { "App.xaml", App_xaml },
            { "MainWindow.xaml", MainWindow_xaml },
            { "Resources.xaml", Resources_xaml },

            { "Samples/Button.xaml", Button_xaml },
            { "Samples/RepeatButton.xaml", RepeatButton_xaml },
            { "Samples/ToggleButton.xaml", ToggleButton_xaml },
            { "Samples/CheckBox.xaml", CheckBox_xaml },
            { "Samples/RadioButton.xaml", RadioButton_xaml },
            { "Samples/Slider.xaml", Slider_xaml },
            { "Samples/TextBlock.xaml", TextBlock_xaml },
            { "Samples/TextBox.xaml", TextBox_xaml },
            { "Samples/PasswordBox.xaml", PasswordBox_xaml },
            { "Samples/Hyperlink.xaml", Hyperlink_xaml },
            { "Samples/ItemsControl.xaml", ItemsControl_xaml },
            { "Samples/ComboBox.xaml", ComboBox_xaml },
            { "Samples/ListBox.xaml", ListBox_xaml },
            { "Samples/ListView.xaml", ListView_xaml },
            { "Samples/TreeView.xaml", TreeView_xaml },
            { "Samples/TabControl.xaml", TabControl_xaml },
            { "Samples/Canvas.xaml", Canvas_xaml },
            { "Samples/StackPanel.xaml", StackPanel_xaml },
            { "Samples/WrapPanel.xaml", WrapPanel_xaml },
            { "Samples/DockPanel.xaml", DockPanel_xaml },
            { "Samples/Grid.xaml", Grid_xaml },
            { "Samples/UniformGrid.xaml", UniformGrid_xaml },
            { "Samples/GroupBox.xaml", GroupBox_xaml },
            { "Samples/Expander.xaml", Expander_xaml },
            { "Samples/ScrollViewer.xaml", ScrollViewer_xaml },
            { "Samples/Menu.xaml", Menu_xaml },
            { "Samples/ContextMenu.xaml", ContextMenu_xaml },
            { "Samples/ToolBar.xaml", ToolBar_xaml },
            { "Samples/StatusBar.xaml", StatusBar_xaml },
            { "Samples/ProgressBar.xaml", ProgressBar_xaml },
            { "Samples/ToolTip.xaml", ToolTip_xaml },
            { "Samples/Brushes.xaml", Brushes_xaml },
            { "Samples/Image.xaml", Image_xaml },
            { "Samples/Effects.xaml", Effects_xaml },
            { "Samples/Animation.xaml", Animation_xaml }
        };

        return *new EmbeddedXamlProvider(xamls);
    }

    Noesis::Ptr<FontProvider> GetFontProvider() const override
    {
        EmbeddedFont fonts[] =
        {
            { "Samples/Fonts", Muli_Regular_ttf },
            { "Samples/Fonts", Muli_Bold_ttf },
            { "Samples/Fonts", Muli_Italic_ttf },
            { "Samples/Fonts", Caladea_Regular_ttf },
            { "Samples/Fonts", CourierPrime_Regular_ttf },
            { "Samples/Fonts", WidgetIcons_ttf }
        };

        return *new EmbeddedFontProvider(fonts);
    }

    Noesis::Ptr<TextureProvider> GetTextureProvider() const override
    {
        EmbeddedTexture textures[] =
        {
            { "Samples/Images/file.png", file_png },
            { "Samples/Images/folder-closed.png", folder_closed_png },
            { "Samples/Images/folder-open.png", folder_open_png },
            { "Samples/Images/recycling-bin.png", recycling_bin_png },
            { "Samples/Images/floppy-disk.png", floppy_disk_png },
            { "Samples/Images/search.png", search_png },
            { "Samples/Images/Nature.png", Nature_png }
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
