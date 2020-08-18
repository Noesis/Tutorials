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
    public partial class MainWindow : Window
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
                CompositionTarget.Rendering += (s_, e_) => renderingCallback?.Invoke();
            };
        }

        void StartTestST()
        {
            var rand = new Random(0);
            var sw = new Stopwatch();
            sw.Start();

            breakTest = false;

            processed = 0;

            prevTicks = sw.ElapsedTicks;
            prevProcessed = 0;
            avgSum = 0;
            avgN = 0;

            renderingCallback = () =>
            {
                long start = sw.ElapsedTicks;
                long ticks = start;

                if (breakTest)
                {
                    double avg = avgSum / (double)avgN;
                    dopes.Text = string.Format("{0:F2} Dopes/s (AVG)", avg);

                    renderingCallback = null;
                    return;
                }

                //60hz, 16ms to build the frame
                while (((ticks - start) / (double)Stopwatch.Frequency) * 1000 < 16)
                {
                    ticks = sw.ElapsedTicks;

                    TextBlock label = new TextBlock();
                    label.Text = "Dope";
                    label.Foreground = new SolidColorBrush { Color = Color.FromRgb((byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255)) }; ;
                    label.RenderTransformOrigin = new Point(0.5f, 0.5f);
                    label.RenderTransform = new RotateTransform { Angle = (float)(rand.NextDouble() * 360.0) };

                    Canvas.SetLeft(label, (float)rand.NextDouble() * absolute.ActualWidth);
                    Canvas.SetTop(label, (float)rand.NextDouble() * absolute.ActualHeight);

                    if (processed > max)
                    {
                        absolute.Children.RemoveAt(0);
                    }

                    absolute.Children.Add(label);

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
            };
        }

        void StartTestReuseST()
        {
            var rand = new Random(0);
            var sw = new Stopwatch();
            sw.Start();

            breakTest = false;

            processed = 0;

            prevTicks = sw.ElapsedTicks;
            prevProcessed = 0;
            avgSum = 0;
            avgN = 0;

            renderingCallback = () =>
            {
                long start = sw.ElapsedTicks;
                long ticks = start;

                if (breakTest)
                {
                    double avg = avgSum / (double)avgN;
                    dopes.Text = string.Format("{0:F2} Dopes/s (AVG)", avg);

                    renderingCallback = null;
                    return;
                }

                //60hz, 16ms to build the frame
                while (((ticks - start) / (double)Stopwatch.Frequency) * 1000 < 16)
                {
                    ticks = sw.ElapsedTicks;

                    TextBlock label;
                    if (cache.Count == 0)
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
                        label = cache[cache.Count - 1];
                        cache.RemoveAt(cache.Count - 1);
                    }

                    ((SolidColorBrush)label.Foreground).Color = Color.FromRgb((byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255));
                    ((RotateTransform)label.RenderTransform).Angle = (float)(rand.NextDouble() * 360.0);

                    Canvas.SetLeft(label, (float)rand.NextDouble() * absolute.ActualWidth);
                    Canvas.SetTop(label, (float)rand.NextDouble() * absolute.ActualHeight);

                    if (processed > max)
                    {
                        cache.Add((TextBlock)absolute.Children[0]);
                        absolute.Children.RemoveAt(0);
                    }

                    absolute.Children.Add(label);

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
            };
        }

        void StartTestBindingST()
        {
            var rand = new Random(0);
            var sw = new Stopwatch();
            sw.Start();

            breakTest = false;

            processed = 0;

            prevTicks = sw.ElapsedTicks;
            prevProcessed = 0;
            avgSum = 0;
            avgN = 0;

            items.ItemsSource = list;

            renderingCallback = () =>
            {
                long start = sw.ElapsedTicks;
                long ticks = start;

                if (breakTest)
                {
                    double avg = avgSum / (double)avgN;
                    dopes.Text = string.Format("{0:F2} Dopes/s (AVG)", avg);

                    renderingCallback = null;
                    return;
                }

                //60hz, 16ms to build the frame
                while (((ticks - start) / (double)Stopwatch.Frequency) * 1000 < 16)
                {
                    ticks = sw.ElapsedTicks;

                    Item item = list[processed % max];
                    item.Color = Color.FromRgb((byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255), (byte)(rand.NextDouble() * 255));
                    item.Rotation = (float)(rand.NextDouble() * 360.0);
                    item.Left = (float)(rand.NextDouble() * absolute.ActualWidth);
                    item.Top = (float)(rand.NextDouble() * absolute.ActualHeight);

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
            };
        }

        void StartTestChangeST()
        {
            var rand = new Random(0);
            var sw = new Stopwatch();
            sw.Start();

            breakTest = false;

            processed = 0;

            prevTicks = sw.ElapsedTicks;
            prevProcessed = 0;
            avgSum = 0;
            avgN = 0;

            string[] texts = { "Dope", "dOpe", "doPe", "dopE", "DOpe", "dOPe", "doPE" };

            renderingCallback = () =>
            {
                long start = sw.ElapsedTicks;
                long ticks = start;

                if (breakTest)
                {
                    double avg = avgSum / (double)avgN;
                    dopes.Text = string.Format("{0:F2} Dopes/s (AVG)", avg);

                    renderingCallback = null;
                    return;
                }

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

                        Canvas.SetLeft(label, (float)rand.NextDouble() * absolute.ActualWidth);
                        Canvas.SetTop(label, (float)rand.NextDouble() * absolute.ActualHeight);

                        absolute.Children.Add(label);
                    }
                    else
                    {
                        TextBlock label = (TextBlock)absolute.Children[processed % max];
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
            };
        }

        void SetControlsAtStart()
        {
            stop.Visibility = Visibility.Visible;
            dopes.Visibility = Visibility.Visible;
            startST.Visibility = Visibility.Collapsed;
            startReuseST.Visibility = Visibility.Collapsed;
            startBindingST.Visibility = Visibility.Collapsed;
            startChangeST.Visibility = Visibility.Collapsed;

            items.ItemsSource = null;
            absolute.Children.Clear();
            dopes.Text = "Warming up..";
        }

        private void Stop_Clicked(object o, RoutedEventArgs e)
        {
            breakTest = true;
            stop.Visibility = Visibility.Collapsed;
            startST.Visibility = Visibility.Visible;
            startReuseST.Visibility = Visibility.Visible;
            startBindingST.Visibility = Visibility.Visible;
            startChangeST.Visibility = Visibility.Visible;

            cache.Clear();
        }

        private void startST_Clicked(object o, RoutedEventArgs e)
        {
            SetControlsAtStart();
            StartTestST();
        }

        private void startReuseST_Clicked(object o, RoutedEventArgs e)
        {
            SetControlsAtStart();
            StartTestReuseST();
        }

        private void startBindingST_Clicked(object o, RoutedEventArgs e)
        {
            SetControlsAtStart();
            StartTestBindingST();
        }

        void startChangeST_Clicked(object o, RoutedEventArgs e)
        {
            SetControlsAtStart();
            StartTestChangeST();
        }

        volatile bool breakTest = false;
        const int max = 600;

        int processed = 0;

        long prevTicks = 0;
        int prevProcessed = 0;
        double avgSum = 0;
        int avgN = 0;

        List<TextBlock> cache = new List<TextBlock>();
        List<Item> list = new List<Item>();

        private delegate void RenderingCallback();
        private RenderingCallback renderingCallback = null;
    }
}
