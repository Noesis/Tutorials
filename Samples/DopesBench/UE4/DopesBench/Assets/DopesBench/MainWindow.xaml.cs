using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Reflection;

namespace DopesBench
{
    public class Item : INotifyPropertyChanged
    {
        private float left;
        private float top;
        private float rotation;
        private Color color;

        public float Left
        {
            get { return left; }
            set
            {
                left = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Left)));
            }
        }
        public float Top
        {
            get { return top; }
            set
            {
                top = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Top)));
            }
        }
        public float Rotation
        {
            get { return rotation; }
            set
            {
                rotation = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Rotation)));
            }
        }
        public Color Color
        {
            get { return color; }
            set
            {
                color = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Color)));
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Page
    {
        public MainWindow()
        {
            InitializeComponent();

            for (int i = 0; i < max; i++)
            {
                list.Add(new Item());
            }

            Loaded += (s, e) =>
            {
                CompositionTarget.Rendering += (s_, e_) =>
                {
                    switch (runningTest)
                    {
                        case 0: break;
                        case 1: TestBuild(); break;
                        case 2: TestReuse(); break;
                        case 3: TestBinding(); break;
                        case 4: TestChange(); break;
                        default: break;
                    }
                };
            };
        }

        void TestBuild()
        {
            long start = sw.ElapsedTicks;
            long ticks = start;

            //60hz, 16ms to build the frame
            while (((ticks - start) / (double)Stopwatch.Frequency) * 1000 < 16)
            {
                ticks = sw.ElapsedTicks;

                TextBlock label = new TextBlock();
                label.Text = "Dope";
                label.Foreground = new SolidColorBrush { Color = Color.FromRgb((byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255)) }; ;
                label.RenderTransformOrigin = new Point(0.5f, 0.5f);
                label.RenderTransform = new RotateTransform { Angle = (float)(rand.NextDouble() * 360.0) };

                Canvas.SetLeft(label, (float)rand.NextDouble() * canvas.ActualWidth);
                Canvas.SetTop(label, (float)rand.NextDouble() * canvas.ActualHeight);

                if (processed > max)
                {
                    canvas.Children.RemoveAt(0);
                }

                canvas.Children.Add(label);

                processed++;

                double seconds = (ticks - prevTicks) / (double)Stopwatch.Frequency;
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        dopes.Text = string.Format("{0:F2} Dopes/s", r);
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        }

        void TestReuse()
        {
            long start = sw.ElapsedTicks;
            long ticks = start;

            //60hz, 16ms to build the frame
            while (((ticks - start) / (double)Stopwatch.Frequency) * 1000 < 16)
            {
                ticks = sw.ElapsedTicks;

                TextBlock label;
                if (processed < max)
                {
                    label = new TextBlock()
                    {
                        Text = "Dope",
                        Foreground = new SolidColorBrush(),
                        RenderTransformOrigin = new Point(0.5f, 0.5f),
                        RenderTransform = new RotateTransform()
                    };
                }
                else
                {
                    label = (TextBlock)canvas.Children[0];
                    canvas.Children.RemoveAt(0);
                }

                ((SolidColorBrush)label.Foreground).Color = Color.FromRgb((byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255));
                ((RotateTransform)label.RenderTransform).Angle = (float)(rand.NextDouble() * 360.0);

                Canvas.SetLeft(label, (float)rand.NextDouble() * canvas.ActualWidth);
                Canvas.SetTop(label, (float)rand.NextDouble() * canvas.ActualHeight);

                canvas.Children.Add(label);

                processed++;

                double seconds = (ticks - prevTicks) / (double)Stopwatch.Frequency;
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        dopes.Text = string.Format("{0:F2} Dopes/s", r);
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        }

        void TestBinding()
        {
            long start = sw.ElapsedTicks;
            long ticks = start;

            //60hz, 16ms to build the frame
            while (((ticks - start) / (double)Stopwatch.Frequency) * 1000 < 16)
            {
                ticks = sw.ElapsedTicks;

                Item item = list[processed % max];
                item.Color = Color.FromRgb((byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255));
                item.Rotation = (float)(rand.NextDouble() * 360.0);
                item.Left = (float)(rand.NextDouble() * canvas.ActualWidth);
                item.Top = (float)(rand.NextDouble() * canvas.ActualHeight);

                processed++;

                double seconds = (ticks - prevTicks) / (double)Stopwatch.Frequency;
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        dopes.Text = string.Format("{0:F2} Dopes/s", r);
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        }

        void TestChange()
        {
            long start = sw.ElapsedTicks;
            long ticks = start;

            //60hz, 16ms to build the frame
            while (((ticks - start) / (double)Stopwatch.Frequency) * 1000 < 16)
            {
                ticks = sw.ElapsedTicks;

                if (processed < max)
                {
                    TextBlock label = new TextBlock();
                    label.Text = "Dope";
                    label.Foreground = new SolidColorBrush { Color = Color.FromRgb((byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255)) }; ;
                    label.RenderTransformOrigin = new Point(0.5f, 0.5f);
                    label.RenderTransform = new RotateTransform { Angle = (float)(rand.NextDouble() * 360.0) };

                    Canvas.SetLeft(label, (float)rand.NextDouble() * canvas.ActualWidth);
                    Canvas.SetTop(label, (float)rand.NextDouble() * canvas.ActualHeight);

                    canvas.Children.Add(label);
                }
                else
                {
                    TextBlock label = (TextBlock)canvas.Children[processed % max];
                    label.Text = texts[processed % texts.Length];
                }

                processed++;

                double seconds = (ticks - prevTicks) / (double)Stopwatch.Frequency;
                if (seconds * 1000 > 500)
                {
                    double r = (double)(processed - prevProcessed) / seconds;
                    prevTicks = ticks;
                    prevProcessed = processed;

                    if (processed > max)
                    {
                        dopes.Text = string.Format("{0:F2} Dopes/s", r);
                        avgSum += r;
                        avgN++;
                    }
                }
            }
        }

        void StartTest(int test)
        {
            runningTest = test;

            stop.Visibility = Visibility.Visible;
            dopes.Visibility = Visibility.Visible;
            build.Visibility = Visibility.Collapsed;
            reuse.Visibility = Visibility.Collapsed;
            binding.Visibility = Visibility.Collapsed;
            change.Visibility = Visibility.Collapsed;

            items.ItemsSource = null;
            canvas.Children.Clear();
            dopes.Text = "Warming up..";

            processed = 0;

            sw.Start();
            prevTicks = sw.ElapsedTicks;
            prevProcessed = 0;
            avgSum = 0;
            avgN = 0;
        }

        private void Stop_Clicked(object o, RoutedEventArgs e)
        {
            stop.Visibility = Visibility.Collapsed;
            build.Visibility = Visibility.Visible;
            reuse.Visibility = Visibility.Visible;
            binding.Visibility = Visibility.Visible;
            change.Visibility = Visibility.Visible;

            double avg = avgSum / (double)avgN;
            dopes.Text = string.Format("{0:F2} Dopes/s (AVG)", avg);

            runningTest = 0;
        }

        private void Build_Clicked(object o, RoutedEventArgs e)
        {
            StartTest(1);
        }

        private void Reuse_Clicked(object o, RoutedEventArgs e)
        {
            StartTest(2);
        }

        private void Binding_Clicked(object o, RoutedEventArgs e)
        {
            StartTest(3);
            items.ItemsSource = list;
        }

        void Change_Clicked(object o, RoutedEventArgs e)
        {
            StartTest(4);
        }

        const int max = 600;

        static string[] texts = { "Dope", "dOpe", "doPe", "dopE", "DOpe", "dOPe", "doPE" };

        int processed = 0;

        long prevTicks = 0;
        int prevProcessed = 0;
        double avgSum = 0;
        int avgN = 0;

        Random rand = new Random(0);
        Stopwatch sw = new Stopwatch();

        List<Item> list = new List<Item>();

        int runningTest = 0;
    }
}
