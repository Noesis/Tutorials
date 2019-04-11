#if NOESIS
using Noesis;
using NoesisApp;
using System;
#else
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
#endif

namespace BlendTutorial
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Rectangle SelectedRectangle = null;
        private Border SelectionBorder = null;
        private bool IsDragging = false;
        private Point Offset = new Point(0, 0);

        public MainWindow()
        {
            this.InitializeComponent();

            this.SelectionBorder = new Border();
            this.SelectionBorder.BorderBrush = (Brush)Brushes.Black.Clone();
            this.SelectionBorder.BorderBrush.Opacity = 0.5f;
            this.SelectionBorder.BorderThickness = new Thickness(2);
            this.SelectionBorder.CornerRadius = new CornerRadius(4);
            this.SelectionBorder.Margin = new Thickness(-3, -3, 0, 0);
            this.SelectionBorder.Padding = new Thickness(2, 2, 0, 0);
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            ClearSelection();

            this.SelectedRectangle = new Rectangle();
            this.SelectedRectangle.Fill = (Brush)Brushes.Red.Clone();
            this.SelectedRectangle.Stroke = (Brush)Brushes.Transparent.Clone();
            this.SelectedRectangle.StrokeThickness = 5;

            this.PositionLeft.Value = 0;
            this.PositionTop.Value = 0;
            this.SizeWidth.Value = 100;
            this.SizeHeight.Value = 100;
            this.ColorSelect.Color = (SolidColorBrush)Brushes.Red.Clone();

            BindSelection();

            this.ContainerCanvas.Children.Add(this.SelectedRectangle);

            SetSelection();
        }

        private void RemoveButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.SelectedRectangle != null)
            {
                this.ContainerCanvas.Children.Remove(this.SelectedRectangle);
                this.ContainerCanvas.Children.Remove(this.SelectionBorder);

                this.SelectedRectangle = null;
                this.SelectionBorder.Child = null;
            }
        }

        private void ContainerBorder_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle newSelection = e.Source as Rectangle;
            if (newSelection != this.SelectedRectangle)
            {
                ClearSelection();

                this.SelectedRectangle = newSelection;

                if (this.SelectedRectangle != null)
                {
                    this.PositionLeft.Value = Canvas.GetLeft(this.SelectedRectangle);
                    this.PositionTop.Value = Canvas.GetTop(this.SelectedRectangle);
                    this.SizeWidth.Value = this.SelectedRectangle.Width;
                    this.SizeHeight.Value = this.SelectedRectangle.Height;
                    this.ColorSelect.Color = (this.FillSelected.IsChecked.Value ? this.SelectedRectangle.Fill : this.SelectedRectangle.Stroke) as SolidColorBrush;

                    BindSelection();

                    SetSelection();
                }
            }

            if (this.SelectedRectangle != null)
            {
                this.ContainerBorder.CaptureMouse();
                this.IsDragging = true;
                this.Offset = e.GetPosition(this.SelectedRectangle);
            }
        }

        private void ContainerBorder_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (this.IsDragging)
            {
                this.ContainerBorder.ReleaseMouseCapture();
                this.IsDragging = false;
            }
        }

        private void ContainerBorder_MouseMove(object sender, MouseEventArgs e)
        {
            if (this.IsDragging && this.SelectedRectangle != null)
            {
                Point max = new Point(
                    this.ContainerBorder.ActualWidth - this.SelectedRectangle.ActualWidth - 5,
                    this.ContainerBorder.ActualHeight - this.SelectedRectangle.ActualHeight - 5);
                Point p = e.GetPosition(this.ContainerBorder);
                Canvas.SetLeft(this.SelectedRectangle, Math.Min(p.X - this.Offset.X - 2, max.X));
                Canvas.SetTop(this.SelectedRectangle, Math.Min(p.Y - this.Offset.Y - 2, max.Y));
            }
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            if (this.SelectedRectangle != null)
            {
                if (this.FillSelected.IsChecked.Value)
                {
                    this.SelectedRectangle.Stroke = (Brush)this.ColorSelect.Color.Clone();
                    this.ColorSelect.Color = this.SelectedRectangle.Fill as SolidColorBrush;
                    Binding binding = new Binding("Color") { Source = this.ColorSelect };
                    this.SelectedRectangle.SetBinding(Shape.FillProperty, binding);
                }
                else
                {
                    this.SelectedRectangle.Fill = (Brush)this.ColorSelect.Color.Clone();
                    this.ColorSelect.Color = this.SelectedRectangle.Stroke as SolidColorBrush;
                    Binding binding = new Binding("Color") { Source = this.ColorSelect };
                    this.SelectedRectangle.SetBinding(Shape.StrokeProperty, binding);
                }
            }
        }

        private void ClearSelection()
        {
            if (this.SelectedRectangle != null)
            {
                BindingOperations.ClearBinding(this.SelectedRectangle, Canvas.LeftProperty);
                BindingOperations.ClearBinding(this.SelectedRectangle, Canvas.TopProperty);
                BindingOperations.ClearBinding(this.SelectedRectangle, WidthProperty);
                BindingOperations.ClearBinding(this.SelectedRectangle, HeightProperty);
                Canvas.SetLeft(this.SelectedRectangle, this.PositionLeft.Value);
                Canvas.SetTop(this.SelectedRectangle, this.PositionTop.Value);
                this.SelectedRectangle.Width = this.SizeWidth.Value;
                this.SelectedRectangle.Height = this.SizeHeight.Value;
                if (this.FillSelected.IsChecked.Value)
                {
                    this.SelectedRectangle.Fill = (Brush)this.ColorSelect.Color.Clone();
                }
                else
                {
                    this.SelectedRectangle.Stroke = (Brush)this.ColorSelect.Color.Clone();
                }

                this.ContainerCanvas.Children.Remove(this.SelectionBorder);
            }
        }
        
        private void BindSelection()
        {
            Binding binding;

            binding = new Binding("Value") { Source = this.PositionLeft, Mode = BindingMode.TwoWay };
            this.SelectedRectangle.SetBinding(Canvas.LeftProperty, binding);
            binding = new Binding("Value") { Source = this.PositionTop, Mode = BindingMode.TwoWay };
            this.SelectedRectangle.SetBinding(Canvas.TopProperty, binding);
            binding = new Binding("Value") { Source = this.SizeWidth };
            this.SelectedRectangle.SetBinding(FrameworkElement.WidthProperty, binding);
            binding = new Binding("Value") { Source = this.SizeHeight };
            this.SelectedRectangle.SetBinding(FrameworkElement.HeightProperty, binding);
            binding = new Binding("Color") { Source = this.ColorSelect };
            this.SelectedRectangle.SetBinding(this.FillSelected.IsChecked.Value ? Shape.FillProperty : Shape.StrokeProperty, binding);
        }
        
        private void SetSelection()
        {
            Border selection = new Border();

            Binding binding;

            binding = new Binding("Width") { Source = this.SelectedRectangle };
            selection.SetBinding(FrameworkElement.WidthProperty, binding);
            binding = new Binding("Height") { Source = this.SelectedRectangle };
            selection.SetBinding(FrameworkElement.HeightProperty, binding);

            this.SelectionBorder.Child = selection;

            binding = new Binding("(Canvas.Left)") { Source = this.SelectedRectangle };
            this.SelectionBorder.SetBinding(Canvas.LeftProperty, binding);
            binding = new Binding("(Canvas.Top)") { Source = this.SelectedRectangle };
            this.SelectionBorder.SetBinding(Canvas.TopProperty, binding);

            this.ContainerCanvas.Children.Add(this.SelectionBorder);
        }

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "MainWindow.xaml");

            PositionLeft = (Slider)FindName("PositionLeft");
            PositionTop = (Slider)FindName("PositionTop");
            SizeWidth = (Slider)FindName("SizeWidth");
            SizeHeight = (Slider)FindName("SizeHeight");
            ColorSelect = (ColorSelector)FindName("ColorSelect");
            ContainerBorder = (Border)FindName("ContainerBorder");
            ContainerCanvas = (Canvas)FindName("ContainerCanvas");
            FillSelected = (RadioButton)FindName("FillSelected");
        }

        protected override bool ConnectEvent(object source, string eventName, string handlerName)
        {
            if (eventName == "Click" && handlerName == "AddButton_Click")
            {
                ((Button)source).Click += AddButton_Click;
                return true;
            }
            if (eventName == "Click" && handlerName == "RemoveButton_Click")
            {
                ((Button)source).Click += RemoveButton_Click;
                return true;
            }
            if (eventName == "PreviewMouseLeftButtonDown" && handlerName == "ContainerBorder_MouseDown")
            {
                ((Border)source).PreviewMouseLeftButtonDown += ContainerBorder_MouseDown;
                return true;
            }
            if (eventName == "PreviewMouseLeftButtonUp" && handlerName == "ContainerBorder_MouseUp")
            {
                ((Border)source).PreviewMouseLeftButtonUp += ContainerBorder_MouseUp;
                return true;
            }
            if (eventName == "PreviewMouseMove" && handlerName == "ContainerBorder_MouseMove")
            {
                ((Border)source).PreviewMouseMove += ContainerBorder_MouseMove;
                return true;
            }
            if (eventName == "Checked" && handlerName == "RadioButton_Checked")
            {
                ((StackPanel)source).AddHandler(RadioButton.CheckedEvent, new RoutedEventHandler(RadioButton_Checked));
                return true;
            }
            return false;
        }

        private Slider PositionLeft = null;
        private Slider PositionTop = null;
        private Slider SizeWidth = null;
        private Slider SizeHeight = null;
        private ColorSelector ColorSelect = null;
        private Border ContainerBorder = null;
        private Canvas ContainerCanvas = null;
        private RadioButton FillSelected = null;
#endif
    }
}
