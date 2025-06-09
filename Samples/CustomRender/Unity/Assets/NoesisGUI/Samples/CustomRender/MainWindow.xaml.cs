#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using System.Diagnostics;
using Float = System.Single;
#else
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using Float = System.Double;
#endif

namespace CustomRender
{
    public class Game : FrameworkElement
    {
        public Game()
        {
            Reset();

#if NOESIS
            Loaded += (s, e) => { View.Rendering += (s2, e2) => InvalidateVisual(); };
#else
            CompositionTarget.Rendering += (s, e) => { InvalidateVisual(); };
#endif
        }

        private void Reset()
        {
            mClock.Restart();
            mLastTime = mClock.ElapsedTicks;

            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 13; j++)
                    mBlocks[i][j] = false;

            mPadX = mPosX = ScreenWidth / 2.0f;
            mPosY = ScreenHeight - PadHeight - 50.0f;
            mVelX = -2.0f;
            mVelY = -4.0f;
        }

        protected override void OnRender(DrawingContext context)
        {
            long t = mClock.ElapsedTicks;
            Float dt = (Float)(t - mLastTime) / Stopwatch.Frequency;
            mLastTime = t;

            // Draw background
            context.DrawRectangle(Brushes.Black, null, new Rect(0, 0, ScreenWidth, ScreenHeight));

            // Draw pad
            {
                Point mouse = Mouse.GetPosition(this);
                if (mouse.X > 0.0f && mouse.X < ScreenWidth && mouse.Y > 0.0f && mouse.Y < ScreenHeight)
                {
                    mPadX = Math.Min(Math.Max(mouse.X, PadWidth * 0.5f), ScreenWidth - PadWidth * 0.5f);
                }
                else
                {
                    if (Keyboard.IsKeyDown(Key.Left)
#if NOESIS
                        || Keyboard.IsKeyDown(Key.GamepadLeft)
#endif
                        )
                    {
                        mPadX = Math.Max(PadWidth * 0.5f, mPadX - 600.0f * dt);
                    }
                    if (Keyboard.IsKeyDown(Key.Right)
#if NOESIS
                        || Keyboard.IsKeyDown(Key.GamepadRight)
#endif
                        )
                    {
                        mPadX = Math.Min(mPadX + 600.0f * dt, Width - PadWidth * 0.5f);
                    }
                }

                Float x0 = mPadX - PadWidth * 0.5f;
                Float x1 = x0 + PadWidth;
                Float y0 = 550.0f - PadHeight * 0.5f;
                Float y1 = y0 + PadHeight;

                if (mPosX >= x0 && mPosX <= x1 && mPosY >= y0 && mPosY <= y1)
                {
                    if (mVelY > 0.0) mVelY = -mVelY;

                    Float vScale = (mPosX - mPadX) / (PadWidth * 0.5f);
                    mVelX += vScale * 2.0f;
                }

                context.DrawRectangle(Brushes.Silver, null, new Rect(new Point(x0 + 18.0f, y0), new Point(x1 - 18.0f, y0 + 4.0f)));
                context.DrawRectangle(Brushes.Lavender, null, new Rect(new Point(x0 + 18.0f, y0 + 4.0f), new Point(x1 - 18.0f, y0 + 8.0f)));
                context.DrawRectangle(Brushes.Silver, null, new Rect(new Point(x0 + 18.0f, y0 + 8.0f), new Point(x1 - 18.0f, y0 + 15.0f)));
                context.DrawRectangle(Brushes.SlateGray, null, new Rect(new Point(x0 + 18.0f, y0 + 15.0f), new Point(x1 - 18.0f, y1)));

                context.DrawRectangle(Brushes.Gold, null, new Rect(new Point(x1 - 16.0f, y0), new Point(x1, y0 + 4.0f)));
                context.DrawRectangle(Brushes.Khaki, null, new Rect(new Point(x1 - 16.0f, y0 + 4.0f), new Point(x1, y0 + 8.0f)));
                context.DrawRectangle(Brushes.Gold, null, new Rect(new Point(x1 - 16.0f, y0 + 8.0f), new Point(x1, y0 + 15.0f)));
                context.DrawRectangle(Brushes.Goldenrod, null, new Rect(new Point(x1 - 16.0f, y0 + 15.0f), new Point(x1, y1)));

                context.DrawRectangle(Brushes.Gold, null, new Rect(new Point(x0, y0), new Point(x0 + 16.0f, y0 + 4.0f)));
                context.DrawRectangle(Brushes.Khaki, null, new Rect(new Point(x0, y0 + 4.0f), new Point(x0 + 16.0f, y0 + 8.0f)));
                context.DrawRectangle(Brushes.Gold, null, new Rect(new Point(x0, y0 + 8.0f), new Point(x0 + 16.0f, y0 + 15.0f)));
                context.DrawRectangle(Brushes.Goldenrod, null, new Rect(new Point(x0, y0 + 15.0f), new Point(x0 + 16.0f, y1)));
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

                        Float x0 = j * BlockWidth;
                        Float x1 = x0 + BlockWidth;
                        Float y0 = i * BlockHeight + 100.0f;
                        Float y1 = y0 + BlockHeight;

                        if (mPosX >= x0 && mPosX <= x1 && mPosY >= y0 && mPosY <= y1)
                        {
                            mBlocks[i][j] = true;

                            Float dx0 = mPosX - x0;
                            Float dx1 = x1 - mPosX;
                            Float dy0 = mPosY - y0;
                            Float dy1 = y1 - mPosY;

                            if (Math.Min(dx0, dx1) < Math.Min(dy0, dy1))
                            {
                                mVelX = -mVelX;
                            }
                            else
                            {
                                mVelY = -mVelY;
                            }
                        }

                        context.DrawRectangle(Brushes0[i], null, new Rect(new Point(x0 + 2.0f, y0 + 2.0f), new Point(x1 - 2.0f, y1 - 2.0f)));
                        context.DrawRectangle(Brushes1[i], null, new Rect(new Point(x0 + 5.0f, y0 + 25.0f), new Point(x1 - 2.0f, y1 - 2.0f)));
                        context.DrawRectangle(Brushes1[i], null, new Rect(new Point(x0 + 57.0f, y0 + 5.0f), new Point(x1 - 2.0f, y1 - 2.0f)));
                    }
                }
            }

            // Draw ball
            {
                mPosX += mVelX * dt * 60.0f;
                mPosY += mVelY * dt * 60.0f;
                if (mPosX < 0.0f || mPosX > ScreenWidth) mVelX = -mVelX;
                if (mPosY < 0.0f) mVelY = -mVelY;
                if (mPosY > ScreenHeight) Reset();

                mVelX *= 1.00005f;
                mVelY *= 1.0001f;

                Float x0 = mPosX - 7.0f;
                Float x1 = mPosX + 7.0f;
                Float y0 = mPosY - 7.0f;
                Float y1 = mPosY + 7.0f;

                context.DrawRectangle(Brushes.LightSkyBlue, null, new Rect(new Point(x0 + 2.0f, y0 + 2.0f), new Point(x1 - 2.0f, y1 - 2.0f)));
                context.DrawRectangle(Brushes.Aqua, null, new Rect(new Point(x0 - 2.0f, y0 + 2.0f), new Point(x0 + 2.0f, y1 - 2.0f)));
                context.DrawRectangle(Brushes.Aqua, null, new Rect(new Point(x1 - 2.0f, y0 + 2.0f), new Point(x1 + 2.0f, y1 - 2.0f)));
                context.DrawRectangle(Brushes.Aqua, null, new Rect(new Point(x0 + 2.0f, y0 - 2.0f), new Point(x1 - 2.0f, y0 + 2.0f)));
                context.DrawRectangle(Brushes.Aqua, null, new Rect(new Point(x0 + 2.0f, y1 - 2.0f), new Point(x1 - 2.0f, y1 + 2.0f)));
            }
        }

        const Float ScreenWidth = 800.0f;
        const Float ScreenHeight = 600.0f;
        const Float PadWidth = 85.0f;
        const Float PadHeight = 22.0f;
        const Float BlockWidth = ScreenWidth / 13.0f;
        const Float BlockHeight = 30.0f;

        static Brush[] Brushes0 = new Brush[] { Brushes.Red, Brushes.Gold, Brushes.MediumBlue, Brushes.Magenta, Brushes.Lime };
        static Brush[] Brushes1 = new Brush[] { Brushes.DarkRed, Brushes.Goldenrod, Brushes.Navy, Brushes.DarkMagenta, Brushes.LimeGreen };

        bool[][] mBlocks = new bool[][] { new bool[13], new bool[13], new bool[13], new bool[13], new bool[13] };

        Float mPadX;
        Float mPosX;
        Float mPosY;
        Float mVelX;
        Float mVelY;

        long mLastTime;

        Stopwatch mClock = new Stopwatch();
    }

    /// <summary>
    /// Interaction logic for MainWindow.Xaml
    /// </summary>
    public partial class MainWindow : UserControl
    {
        public MainWindow()
        {
            this.InitializeComponent();
        }

#if NOESIS
        private void InitializeComponent()
        {
            NoesisUnity.LoadComponent(this);
        }
#endif
    }
}
