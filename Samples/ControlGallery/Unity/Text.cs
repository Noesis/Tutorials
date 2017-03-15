////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#if !UNITY_EDITOR

using System;
using System.Windows;
using System.Windows.Media;

namespace NoesisGUIExtensions
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Adds stroke capabilities to text elements.
///
/// Usage:
///
///     <Grid 
///       xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
///       xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
///       xmlns:noesis="clr-namespace:NoesisGUIExtensions">
///         <TextBlock noesis:Text.Stroke="Red" noesis:Text.StrokeThickness="1" Text="Hello"/>
///     </Grid>
///
////////////////////////////////////////////////////////////////////////////////////////////////////
public class Text
{
    public Text()
    {
    }

    /// <summary>
    /// Specifies the brush used to stroke the text
    /// </summary>
    #region Stroke attached property

    public static readonly DependencyProperty StrokeProperty =
        DependencyProperty.RegisterAttached("Stroke", typeof(Brush), typeof(Text),
        new PropertyMetadata(null));

    public static void SetStroke(UIElement element, Brush value)
    {
        element.SetValue(StrokeProperty, value);
    }

    public static Brush GetStroke(UIElement element)
    {
        return (Brush)element.GetValue(StrokeProperty);
    }

    #endregion

    /// <summary>
    /// Specifies the thickness of the text stroke
    /// </summary>
    #region StrokeThickness attached property

    public static readonly DependencyProperty StrokeThicknessProperty =
        DependencyProperty.RegisterAttached("StrokeThickness", typeof(double), typeof(Text),
        new PropertyMetadata(0.0));

    public static void SetStrokeThickness(UIElement element, double value)
    {
        element.SetValue(StrokeThicknessProperty, value);
    }

    public static double GetStrokeThickness(UIElement element)
    {
        return (double)element.GetValue(StrokeThicknessProperty);
    }

    #endregion
}

}

#endif