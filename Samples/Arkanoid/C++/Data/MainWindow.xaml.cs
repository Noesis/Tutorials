using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

namespace Arkanoid
{
    public class Game : FrameworkElement
    {
        public Game()
        {
            _clock = new Stopwatch();
            _clock.Start();

            _random = new Random((int)DateTime.Now.Ticks);

            _pad = new Block();
            for (int i = 0; i < NumBlocks; ++i) _blocks[i] = new Block();

            CompositionTarget.Rendering += (s, e) => { InvalidateVisual(); };
        }

        protected override void OnMouseRightButtonDown(MouseButtonEventArgs e)
        {
            _size = new Size(0.0, 0.0);
            base.OnMouseRightButtonDown(e);
        }

        protected override void OnRender(DrawingContext context)
        {
            // Reset when element changes its size
            if (_size != RenderSize)
            {
                _size = RenderSize;

                _blockSize.Width = _size.Width / 10.0f;
                _blockSize.Height = _size.Height / 12.0f;

                _padSize.Width = _size.Width * 0.125f;
                _padSize.Height = _size.Height * 0.03f;

                _radius = _size.Width * 0.02f;
                _pos.X = _size.Width / 2.0f;
                _pos.Y = _size.Height - _padSize.Height - _radius;
                _velX = -2;
                _velY = -4;

                _pad.l.X = _pos.X - _padSize.Width * 0.5f;
                _pad.l.Y = _size.Height - _padSize.Height;
                _pad.h.X = _pad.l.X + _padSize.Width;
                _pad.h.Y = _pad.l.Y + _padSize.Height;

                if (_pad.color == null)
                {
                    _pad.color = new SolidColorBrush(Colors.White);
                }

                for (int i = 0; i < NumRows; ++i)
                {
                    for (int j = 0; j < NumBlocksPerRow; ++j)
                    {
                        Block block = _blocks[j + i * 10];
                        block.a = true;
                        block.l = new Point(j * _blockSize.Width, i * _blockSize.Height);
                        block.h = new Point((j + 1) * _blockSize.Width, (i + 1) * _blockSize.Height);
                        if (block.color == null)
                        {
                            block.color = new SolidColorBrush();
                        }

                        block.color.Color = Color.FromArgb(255, (byte)_random.Next(0, 255), (byte)_random.Next(0, 255), (byte)_random.Next(0, 255));
                    }
                }
            }

            // Update blocks
            for (int i = 0; i < NumBlocks; ++i)
            {
                Block block = _blocks[i];
                if (!block.a) continue;
                if (!block.inside(_pos)) continue;
                block.a = false;
                double ol = _pos.X - block.l.X;
                double or = block.h.X - _pos.X;
                double ot = _pos.Y - block.l.Y;
                double ob = block.h.Y - _pos.Y;
                double ox = Math.Min(ol, or);
                double oy = Math.Min(ot, ob);
                if (ox < oy)
                {
                    _velX = -_velX;
                }
                else
                {
                    _velY = -_velY;
                }
            }

            float dt = (float)(_clock.ElapsedMilliseconds / 1000.0);
            _clock.Restart();

            // Calculate pad position
            Point mouse = Mouse.GetPosition(this);
            _pad.l.X = Math.Min(Math.Max(0.0f, mouse.X - _padSize.Width * 0.5f), _size.Width - _padSize.Width);
            _pad.h.X = _pad.l.X + _padSize.Width;
            if (_pad.inside(_pos)) _velY = -_velY;

            // Start drawing...

            // background
            context.DrawRectangle(Brushes.Black, null, new Rect(_size));

            // blocks
            for (int i = 0; i < NumBlocks; ++i)
            {
                Block block = _blocks[i];
                if (block.a)
                {
                    Rect rect = new Rect(block.l.X, block.l.Y, block.h.X - block.l.X, block.h.Y - block.l.Y);
                    context.DrawRectangle(block.color, null, rect);
                }
            }

            // pad
            Rect padRect = new Rect(_pad.l.X, _pad.l.Y, _pad.h.X - _pad.l.X, _pad.h.Y - _pad.l.Y);
            context.DrawRectangle(_pad.color, null, padRect);

            // ball
            context.DrawEllipse(_pad.color, null, _pos, _radius, _radius);

            // Update ball position
            _pos.X += _velX * dt * 30.0f;
            _pos.Y += _velY * dt * 30.0f;
            if (_pos.X < 0.0f || _pos.X > _size.Width) _velX = -_velX;
            if (_pos.Y < 0.0f) _velY = -_velY;
            if (_pos.Y > _size.Height) _size = new Size(0.0, 0.0); // reset when ball goes down

            _velX *= 1.00005f;
            _velY *= 1.0001f;
        }

        class Block
        {
            public Point l;
            public Point h;
            public SolidColorBrush color;
            public bool a;

            public bool inside(Point p)
            {
                return (p.X > l.X && p.X < h.X) && (p.Y > l.Y && p.Y < h.Y);
            }
        };

        Stopwatch _clock;
        Random _random;

        const int NumBlocks = 60;
        const int NumRows = 6;
        const int NumBlocksPerRow = NumBlocks / NumRows;

        Block[] _blocks = new Block[NumBlocks];
        Block _pad = new Block();
        Size _blockSize;
        Size _padSize;
        Size _size;
        Point _pos;
        double _radius;
        double _velX;
        double _velY;
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

#if NOESIS
        private void InitializeComponent()
        {
            Noesis.GUI.LoadComponent(this, "Assets/NoesisGUI/Samples/Arkanoid/MainWindow.Xaml");
        }
#endif
    }
}
