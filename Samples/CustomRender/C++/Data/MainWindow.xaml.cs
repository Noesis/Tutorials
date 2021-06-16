using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

namespace CustomRender
{
    public class Game : FrameworkElement
    {
        public Game()
        {
            Reset();
            CompositionTarget.Rendering += (s, e) => { InvalidateVisual(); };
        }

        private void Reset()
        {
            mClock.Restart();
            mLastTime = mClock.ElapsedTicks;

            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 13; j++)
                    mBlocks[i][j] = false;

            mPosX = ScreenWidth / 2.0;
            mPosY = ScreenHeight - PadHeight - 50.0;
            mVelX = -2.0;
            mVelY = -4.0;
        }

        protected override void OnRender(DrawingContext context)
        {
            long t = mClock.ElapsedTicks;
            double dt = (double)(t - mLastTime) / Stopwatch.Frequency;
            mLastTime = t;

            // Draw background
            context.DrawRectangle(Brushes.Black, null, new Rect(0, 0, ScreenWidth, ScreenHeight));

            // Draw pad
            {
                Point mouse = Mouse.GetPosition(this);
                double x = Math.Min(Math.Max(mouse.X, PadWidth * 0.5), ScreenWidth - PadWidth * 0.5);

                double x0 = x - PadWidth * 0.5;
                double x1 = x0 + PadWidth;
                double y0 = 550.0 - PadHeight * 0.5;
                double y1 = y0 + PadHeight;

                if (mPosX >= x0 && mPosX <= x1 && mPosY >= y0 && mPosY <= y1)
                {
                    if (mVelY > 0.0) mVelY = -mVelY;

                    double vScale = (mPosX - x) / (PadWidth * 0.5);
                    mVelX += vScale * 2.0;
                }

                context.DrawRectangle(Brushes.Silver, null,     new Rect(new Point(x0 + 18.0, y0),          new Point(x1 - 18.0, y0 + 4.0)));
                context.DrawRectangle(Brushes.Lavender, null,   new Rect(new Point(x0 + 18.0, y0 + 4.0),    new Point(x1 - 18.0, y0 + 8.0)));
                context.DrawRectangle(Brushes.Silver, null,     new Rect(new Point(x0 + 18.0, y0 + 8.0),    new Point(x1 - 18.0, y0 + 15.0)));
                context.DrawRectangle(Brushes.SlateGray, null,  new Rect(new Point(x0 + 18.0, y0 + 15.0),   new Point(x1 - 18.0, y1)));

                context.DrawRectangle(Brushes.Gold, null,       new Rect(new Point(x1 - 16.0, y0),          new Point(x1, y0 + 4.0)));
                context.DrawRectangle(Brushes.Khaki, null,      new Rect(new Point(x1 - 16.0, y0 + 4.0),    new Point(x1, y0 + 8.0)));
                context.DrawRectangle(Brushes.Gold, null,       new Rect(new Point(x1 - 16.0, y0 + 8.0),    new Point(x1, y0 + 15.0)));
                context.DrawRectangle(Brushes.Goldenrod, null,  new Rect(new Point(x1 - 16.0, y0 + 15.0),   new Point(x1, y1)));

                context.DrawRectangle(Brushes.Gold, null,       new Rect(new Point(x0, y0),                 new Point(x0 + 16.0, y0 + 4.0)));
                context.DrawRectangle(Brushes.Khaki, null,      new Rect(new Point(x0, y0 + 4.0),           new Point(x0 + 16.0, y0 + 8.0)));
                context.DrawRectangle(Brushes.Gold, null,       new Rect(new Point(x0, y0 + 8.0),           new Point(x0 + 16.0, y0 + 15.0)));
                context.DrawRectangle(Brushes.Goldenrod, null,  new Rect(new Point(x0, y0 + 15.0),          new Point(x0 + 16.0, y1)));
            }

            // Draw blocks
            {
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 13; j++)
                    {
                        if (mBlocks[i][j])
                        {
                            continue;
                        }

                        double x0 = j * BlockWidth;
                        double x1 = x0 + BlockWidth;
                        double y0 = i * BlockHeight + 100.0;
                        double y1 = y0 + BlockHeight;

                        if (mPosX >= x0 && mPosX <= x1 && mPosY >= y0 && mPosY <= y1)
                        {
                            mBlocks[i][j] = true;

                            double dx0 = mPosX - x0;
                            double dx1 = x1 - mPosX;
                            double dy0 = mPosY - y0;
                            double dy1 = y1 - mPosY;

                            if (Math.Min(dx0, dx1) < Math.Min(dy0, dy1))
                            {
                                mVelX = -mVelX;
                            }
                            else
                            {
                                mVelY = -mVelY;
                            }
                        }

                        context.DrawRectangle(Brushes0[i], null, new Rect(new Point(x0 + 2.0, y0 + 2.0),    new Point(x1 - 2.0, y1 - 2.0)));
                        context.DrawRectangle(Brushes1[i], null, new Rect(new Point(x0 + 5.0, y0 + 25.0),   new Point(x1 - 2.0, y1 - 2.0)));
                        context.DrawRectangle(Brushes1[i], null, new Rect(new Point(x0 + 57.0, y0 + 5.0),   new Point(x1 - 2.0, y1 - 2.0)));
                    }
                }
            }

            // Draw ball
            {
                mPosX += mVelX * dt * 60.0;
                mPosY += mVelY * dt * 60.0;
                if (mPosX < 0.0 || mPosX > ScreenWidth) mVelX = -mVelX;
                if (mPosY < 0.0) mVelY = -mVelY;
                if (mPosY > ScreenHeight) Reset();

                mVelX *= 1.00005;
                mVelY *= 1.0001;

                double x0 = mPosX - 7.0;
                double x1 = mPosX + 7.0;
                double y0 = mPosY - 7.0;
                double y1 = mPosY + 7.0;

                context.DrawRectangle(Brushes.LightSkyBlue, null,   new Rect(new Point(x0 + 2.0, y0 + 2.0), new Point(x1 - 2.0, y1 - 2.0)));
                context.DrawRectangle(Brushes.Aqua, null,           new Rect(new Point(x0 - 2.0, y0 + 2.0), new Point(x0 + 2.0, y1 - 2.0)));
                context.DrawRectangle(Brushes.Aqua, null,           new Rect(new Point(x1 - 2.0, y0 + 2.0), new Point(x1 + 2.0, y1 - 2.0)));
                context.DrawRectangle(Brushes.Aqua, null,           new Rect(new Point(x0 + 2.0, y0 - 2.0), new Point(x1 - 2.0, y0 + 2.0)));
                context.DrawRectangle(Brushes.Aqua, null,           new Rect(new Point(x0 + 2.0, y1 - 2.0), new Point(x1 - 2.0, y1 + 2.0)));
            }
        }

        const double ScreenWidth = 800.0;
        const double ScreenHeight = 600.0;
        const double PadWidth = 85.0;
        const double PadHeight = 22.0;
        const double BlockWidth = ScreenWidth / 13.0;
        const double BlockHeight = 30.0;

        static Brush[] Brushes0 = new Brush[] { Brushes.Red, Brushes.Gold, Brushes.MediumBlue, Brushes.Magenta, Brushes.Lime };
        static Brush[] Brushes1 = new Brush[] { Brushes.DarkRed, Brushes.Goldenrod, Brushes.Navy, Brushes.DarkMagenta, Brushes.LimeGreen };

        bool[][] mBlocks = new bool[][] { new bool[13], new bool[13], new bool[13], new bool[13], new bool[13] };

        double mPosX;
        double mPosY;
        double mVelX;
        double mVelY;

        long mLastTime;

        Stopwatch mClock = new Stopwatch();
    }

    /// <summary>
    /// Interaction logic for MainWindow.Xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();
        }
    }
}
