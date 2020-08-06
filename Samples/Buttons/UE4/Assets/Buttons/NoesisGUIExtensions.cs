////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Interactivity;

namespace NoesisGUIExtensions
{
    #region Text
    /// <summary>
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
    /// </summary>
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
            new FrameworkPropertyMetadata(null, FrameworkPropertyMetadataOptions.Inherits));

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
            new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.Inherits));

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
    #endregion

    #region Projection
    /// <summary>
    /// Provides a base class for projections, which describe how to transform an object
    /// in 3-D space using perspective transforms.
    /// </summary>
    public abstract class Projection : Animatable
    {
    }

    /// <summary>
    /// Represents a perspective transform (a 3-D-like effect) on an object.
    /// </summary>
    public class PlaneProjection : Projection
    {
        /// <summary>
        /// Gets or sets the x-coordinate of the center of rotation of the object you rotate
        /// </summary>
        #region CenterOfRotationX dependency property

        public double CenterOfRotationX
        {
            get { return (double)GetValue(CenterOfRotationXProperty); }
            set { SetValue(CenterOfRotationXProperty, value); }
        }

        public static readonly DependencyProperty CenterOfRotationXProperty =
            DependencyProperty.Register("CenterOfRotationX", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the y-coordinate of the center of rotation of the object you rotate
        /// </summary>
        #region CenterOfRotationY dependency property

        public double CenterOfRotationY
        {
            get { return (double)GetValue(CenterOfRotationYProperty); }
            set { SetValue(CenterOfRotationYProperty, value); }
        }

        public static readonly DependencyProperty CenterOfRotationYProperty =
            DependencyProperty.Register("CenterOfRotationY", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the z-coordinate of the center of rotation of the object you rotate
        /// </summary>
        #region CenterOfRotationZ dependency property

        public double CenterOfRotationZ
        {
            get { return (double)GetValue(CenterOfRotationZProperty); }
            set { SetValue(CenterOfRotationZProperty, value); }
        }

        public static readonly DependencyProperty CenterOfRotationZProperty =
            DependencyProperty.Register("CenterOfRotationZ", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the distance the object is translated along the x-axis of the screen
        /// </summary>
        #region GlobalOffsetX dependency property

        public double GlobalOffsetX
        {
            get { return (double)GetValue(GlobalOffsetXProperty); }
            set { SetValue(GlobalOffsetXProperty, value); }
        }

        public static readonly DependencyProperty GlobalOffsetXProperty =
            DependencyProperty.Register("GlobalOffsetX", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the distance the object is translated along the y-axis of the screen
        /// </summary>
        #region GlobalOffsetY dependency property

        public double GlobalOffsetY
        {
            get { return (double)GetValue(GlobalOffsetYProperty); }
            set { SetValue(GlobalOffsetYProperty, value); }
        }

        public static readonly DependencyProperty GlobalOffsetYProperty =
            DependencyProperty.Register("GlobalOffsetY", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the distance the object is translated along the z-axis of the screen
        /// </summary>
        #region GlobalOffsetZ dependency property

        public double GlobalOffsetZ
        {
            get { return (double)GetValue(GlobalOffsetZProperty); }
            set { SetValue(GlobalOffsetZProperty, value); }
        }

        public static readonly DependencyProperty GlobalOffsetZProperty =
            DependencyProperty.Register("GlobalOffsetZ", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the distance the object is translated along the x-axis of the plane of the object
        /// </summary>
        #region LocalOffsetX dependency property

        public double LocalOffsetX
        {
            get { return (double)GetValue(LocalOffsetXProperty); }
            set { SetValue(LocalOffsetXProperty, value); }
        }

        public static readonly DependencyProperty LocalOffsetXProperty =
            DependencyProperty.Register("LocalOffsetX", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the distance the object is translated along the y-axis of the plane of the object
        /// </summary>
        #region LocalOffsetY dependency property

        public double LocalOffsetY
        {
            get { return (double)GetValue(LocalOffsetYProperty); }
            set { SetValue(LocalOffsetYProperty, value); }
        }

        public static readonly DependencyProperty LocalOffsetYProperty =
            DependencyProperty.Register("LocalOffsetY", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the distance the object is translated along the z-axis of the plane of the object
        /// </summary>
        #region LocalOffsetZ dependency property

        public double LocalOffsetZ
        {
            get { return (double)GetValue(LocalOffsetZProperty); }
            set { SetValue(LocalOffsetZProperty, value); }
        }

        public static readonly DependencyProperty LocalOffsetZProperty =
            DependencyProperty.Register("LocalOffsetZ", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the number of degrees to rotate the object around the x-axis of rotation
        /// </summary>
        #region RotationX dependency property

        public double RotationX
        {
            get { return (double)GetValue(RotationXProperty); }
            set { SetValue(RotationXProperty, value); }
        }

        public static readonly DependencyProperty RotationXProperty =
            DependencyProperty.Register("RotationX", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the number of degrees to rotate the object around the y-axis of rotation
        /// </summary>
        #region RotationY dependency property

        public double RotationY
        {
            get { return (double)GetValue(RotationYProperty); }
            set { SetValue(RotationYProperty, value); }
        }

        public static readonly DependencyProperty RotationYProperty =
            DependencyProperty.Register("RotationY", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        /// <summary>
        /// Gets or sets the number of degrees to rotate the object around the z-axis of rotation
        /// </summary>
        #region RotationZ dependency property

        public double RotationZ
        {
            get { return (double)GetValue(RotationZProperty); }
            set { SetValue(RotationZProperty, value); }
        }

        public static readonly DependencyProperty RotationZProperty =
            DependencyProperty.Register("RotationZ", typeof(double), typeof(PlaneProjection), new PropertyMetadata(0.0));

        #endregion

        #region CreateInstanceCore implementation

        protected override Freezable CreateInstanceCore()
        {
            return new PlaneProjection();
        }

        #endregion
    }
    #endregion

    #region Element
    public enum PPAAMode
    {
        Default,
        Disabled
    }

    /// <summary>
    /// Extends UI elements with properties not supported by WPF but included in Noesis
    /// </summary>
    public static class Element
    {
        /// <summary>
        /// Adds projection capabilities to UI elements.
        /// It Specifies the Projection object used to project the UI element.
        ///
        /// Usage:
        ///
        ///     <Grid
        ///       xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        ///       xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        ///       xmlns:noesis="clr-namespace:NoesisGUIExtensions">
        ///         <Grid.Resources>
        ///             <Storyboard x:Key="AnimProjection" AutoReverse="True" RepeatBehavior="Forever">
        ///                 <DoubleAnimationUsingKeyFrames
        ///                   Storyboard.TargetProperty="(noesis:Element.Projection).(noesis:PlaneProjection.RotationY)"
        ///                   Storyboard.TargetName="Root">
        ///                     <EasingDoubleKeyFrame KeyTime="0:0:2" Value="-60">
        ///                         <EasingDoubleKeyFrame.EasingFunction>
        ///                             <SineEase EasingMode="EaseInOut"/>
        ///                         </EasingDoubleKeyFrame.EasingFunction>
        ///                     </EasingDoubleKeyFrame>
        ///                 </DoubleAnimationUsingKeyFrames>
        ///             </Storyboard>
        ///         </Grid.Resources>
        ///         <Grid.Triggers>
        ///             <EventTrigger RoutedEvent="FrameworkElement.Loaded">
        ///                 <BeginStoryboard Storyboard="{StaticResource AnimProjection}"/>
        ///             </EventTrigger>
        ///         </Grid.Triggers>
        ///         <Grid x:Name="Root">
        ///             <noesis:Element.Projection>
        ///                 <noesis:PlaneProjection RotationY="60"/>
        ///             </noesis:Element.Projection>
        ///             <Rectangle Width="500" Height="300" Fill="#80FF0000"/>
        ///             <TextBlock
        ///               Text="3D Projection, wow!"
        ///               FontSize="40"
        ///               HorizontalAlignment="Center"
        ///               VerticalAlignment="Center"/>
        ///         </Grid>
        ///     </Grid>
        ///
        /// </summary>
        #region Projection attached property

        public static readonly DependencyProperty ProjectionProperty =
            DependencyProperty.RegisterAttached("Projection", typeof(Projection), typeof(Element),
            new PropertyMetadata(null));

        public static void SetProjection(UIElement element, Projection value)
        {
            element.SetValue(ProjectionProperty, value);
        }

        public static Projection GetProjection(UIElement element)
        {
            return (Projection)element.GetValue(ProjectionProperty);
        }

        #endregion

        /// <summary>
        /// Provides Focus Engagement properties: IsFocusEngagementEnabled and IsFocusEngaged.
        /// They can be used to style Control's focus state accordingly.
        /// </summary>
        #region Focus Engagement attached properties

        public static readonly DependencyProperty IsFocusEngagementEnabledProperty =
            DependencyProperty.RegisterAttached("IsFocusEngagementEnabled", typeof(bool), typeof(Element),
                new PropertyMetadata(false));

        public static void SetIsFocusEngagementEnabled(Control control, bool value)
        {
            control.SetValue(IsFocusEngagementEnabledProperty, value);
        }

        public static bool GetIsFocusEngagementEnabled(Control control)
        {
            return (bool)control.GetValue(IsFocusEngagementEnabledProperty);
        }

        public static readonly DependencyProperty IsFocusEngagedProperty =
            DependencyProperty.RegisterAttached("IsFocusEngaged", typeof(bool), typeof(Element),
                new PropertyMetadata(false));

        public static void SetIsFocusEngaged(Control control, bool value)
        {
            control.SetValue(IsFocusEngagedProperty, value);
        }

        public static bool GetIsFocusEngaged(Control control)
        {
            return (bool)control.GetValue(IsFocusEngagedProperty);
        }

        #endregion

        /// <summary>
        /// Determines whether antialiasing geometry is generated for this element. This property is
        /// inherited down the visual tree.
        /// </summary>
        #region PPAA attached property

        public static readonly DependencyProperty PPAAModeProperty = DependencyProperty.RegisterAttached(
            "PPAAMode", typeof(PPAAMode), typeof(Element),
            new PropertyMetadata(PPAAMode.Default));

        public static void SetPPAAMode(FrameworkElement element, PPAAMode value)
        {
            element.SetValue(PPAAModeProperty, value);
        }

        public static PPAAMode GetPPAAMode(FrameworkElement element)
        {
            return (PPAAMode)element.GetValue(PPAAModeProperty);
        }

        #endregion
    }
    #endregion

    #region StyleInteraction
    /// <summary>
    /// Collection of Behaviors that will be added to the Interaction.Behaviors attached property
    /// </summary>
    public class StyleBehaviorCollection : List<System.Windows.Interactivity.Behavior> { }

    /// <summary>
    /// Collection of Triggers that will be added to the Interaction.Triggers attached property
    /// </summary>
    public class StyleTriggerCollection : List<System.Windows.Interactivity.TriggerBase> { }

    /// <summary>
    /// Provides two attached properties that will allow to specify behaviors and triggers within a Style
    /// </summary>
    public class StyleInteraction
    {
        #region Behaviors property
        public static StyleBehaviorCollection GetBehaviors(DependencyObject d)
        {
            if (d == null) throw new ArgumentNullException("d");
            return (StyleBehaviorCollection)d.GetValue(BehaviorsProperty);
        }

        public static void SetBehaviors(DependencyObject d, StyleBehaviorCollection behaviors)
        {
            if (d == null) throw new ArgumentNullException("d");
            d.SetValue(BehaviorsProperty, behaviors);
        }

        public static readonly DependencyProperty BehaviorsProperty = DependencyProperty.RegisterAttached(
            "Behaviors", typeof(StyleBehaviorCollection), typeof(StyleInteraction),
            new PropertyMetadata(null, OnBehaviorsChanged));

        private static void OnBehaviorsChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            System.Windows.Interactivity.BehaviorCollection behaviors = System.Windows.Interactivity.Interaction.GetBehaviors(d);
            foreach (System.Windows.Interactivity.Behavior behavior in e.NewValue as StyleBehaviorCollection)
            {
                behaviors.Add((System.Windows.Interactivity.Behavior)behavior.Clone());
            }
        }
        #endregion

        #region Triggers property
        public static StyleTriggerCollection GetTriggers(DependencyObject d)
        {
            if (d == null) throw new ArgumentNullException("d");
            return (StyleTriggerCollection)d.GetValue(TriggersProperty);
        }

        public static void SetTriggers(DependencyObject d, StyleTriggerCollection triggers)
        {
            if (d == null) throw new ArgumentNullException("d");
            d.SetValue(TriggersProperty, triggers);
        }

        public static readonly DependencyProperty TriggersProperty = DependencyProperty.RegisterAttached(
            "Triggers", typeof(StyleTriggerCollection), typeof(StyleInteraction),
            new PropertyMetadata(null, OnTriggersChanged));

        private static void OnTriggersChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            System.Windows.Interactivity.TriggerCollection triggers = System.Windows.Interactivity.Interaction.GetTriggers(d);
            foreach (System.Windows.Interactivity.TriggerBase trigger in e.NewValue as StyleTriggerCollection)
            {
                System.Windows.Interactivity.TriggerBase triggerClone = (System.Windows.Interactivity.TriggerBase)trigger.Clone();
                foreach (System.Windows.Interactivity.TriggerAction action in trigger.Actions)
                {
                    System.Windows.Interactivity.TriggerAction actionClone = (System.Windows.Interactivity.TriggerAction)action.Clone();
                    triggerClone.Actions.Add(actionClone);
                }

                triggers.Add(triggerClone);
            }
        }
        #endregion
    }
    #endregion

    #region Interactivity Actions
    public class SetFocusAction : TargetedTriggerAction<UIElement>
    {
        protected override void Invoke(object parameter)
        {
            UIElement element = Target;
            if (element != null)
            {
                element.Focus();
            }
        }
    }

    public class SelectAction : TriggerAction<Control>
    {
        protected override void Invoke(object parameter)
        {
            Control control = AssociatedObject;
            if (control != null)
            {
                Selector.SetIsSelected(control, true);
            }
        }
    }

    public class SelectAllAction : TriggerAction<Control>
    {
        protected override void Invoke(object parameter)
        {
            Control control = AssociatedObject;

            TextBox textBox = control as TextBox;
            if (textBox != null)
            {
                textBox.SelectAll();
                return;
            }

            PasswordBox passwordBox = control as PasswordBox;
            if (passwordBox != null)
            {
                passwordBox.SelectAll();
            }
        }
    }
    #endregion
}
