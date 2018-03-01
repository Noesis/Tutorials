using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Shapes;

namespace BlendTutorial
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Rectangle SelectedRectangle = null;
        private Border SelectionBorder = null;
        
        public MainWindow()
        {
            this.InitializeComponent();

            this.SelectionBorder = new Border();
            this.SelectionBorder.BorderBrush = Brushes.Black.Clone();
            this.SelectionBorder.BorderBrush.Opacity = 0.5;
            this.SelectionBorder.BorderThickness = new Thickness(2);
            this.SelectionBorder.CornerRadius = new CornerRadius(4);
            this.SelectionBorder.Margin = new Thickness(-3, -3, 0, 0);
            this.SelectionBorder.Padding = new Thickness(2, 2, 0, 0);
        }

        private void AddButton_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            ClearSelection();
            
            this.SelectedRectangle = new Rectangle();
            this.SelectedRectangle.Fill = Brushes.Red.Clone();
            this.SelectedRectangle.Stroke = Brushes.Transparent.Clone();
            this.SelectedRectangle.StrokeThickness = 5;

            this.PositionLeft.Value = 0;
            this.PositionTop.Value = 0;
            this.SizeWidth.Value = 100;
            this.SizeHeight.Value = 100;
            this.ColorSelect.Color = Brushes.Red.Clone();

            BindSelection();
            
            this.ContainerCanvas.Children.Add(this.SelectedRectangle);

            SetSelection();
        }

        private void RemoveButton_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (this.SelectedRectangle != null)
            {
                this.ContainerCanvas.Children.Remove(this.SelectedRectangle);
                this.ContainerCanvas.Children.Remove(this.SelectionBorder);
                
                this.SelectedRectangle = null;
                this.SelectionBorder.Child = null;
            }
        }

        private void ContainerBorder_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            HitTestResult hr = VisualTreeHelper.HitTest(this.ContainerBorder, e.GetPosition(this.ContainerBorder));
            
            Rectangle newSelection = hr.VisualHit as Rectangle;
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
            
            e.Handled = true;
        }
        
        private void RadioButton_Checked(object sender, System.Windows.RoutedEventArgs e)
        {
            if (this.SelectedRectangle != null)
            {
                if (this.FillSelected.IsChecked.Value)
                {
                    this.SelectedRectangle.Stroke = this.ColorSelect.Color.Clone();
                    this.ColorSelect.Color = this.SelectedRectangle.Fill as SolidColorBrush;
                    Binding binding = new Binding("Color") { Source = this.ColorSelect };
                    this.SelectedRectangle.SetBinding(Shape.FillProperty, binding);
                }
                else
                {
                    this.SelectedRectangle.Fill = this.ColorSelect.Color.Clone();
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
                Canvas.SetLeft(this.SelectedRectangle, this.PositionLeft.Value);
                Canvas.SetTop(this.SelectedRectangle, this.PositionTop.Value);
                this.SelectedRectangle.Width = this.SizeWidth.Value;
                this.SelectedRectangle.Height = this.SizeHeight.Value;
                if (this.FillSelected.IsChecked.Value)
                {
                    this.SelectedRectangle.Fill = this.ColorSelect.Color.Clone();
                }
                else
                {
                    this.SelectedRectangle.Stroke = this.ColorSelect.Color.Clone();
                }
                
                this.ContainerCanvas.Children.Remove(this.SelectionBorder);
            }
        }
        
        private void BindSelection()
        {
            Binding binding;
            
            binding = new Binding("Value") { Source = this.PositionLeft };
            this.SelectedRectangle.SetBinding(Canvas.LeftProperty, binding);
            binding = new Binding("Value") { Source = this.PositionTop };
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
    }
}
