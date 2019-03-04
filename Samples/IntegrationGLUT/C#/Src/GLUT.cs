using System;
using System.Runtime.InteropServices;

namespace IntegrationGLUT
{
    public static class GLUT
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void DisplayFunc();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void ReshapeFunc(int width, int height);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void PassiveMotionFunc(int x, int y);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void MouseFunc(int button, int state, int x, int y);

        // Display mode bit masks
        public const int RGB            = 0;
        public const int DOUBLE         = 2;
        public const int DEPTH          = 16;
        public const int STENCIL        = 32;

        // Mouse buttons
        public const int LEFT_BUTTON    = 0;
        public const int MIDDLE_BUTTON  = 1;
        public const int RIGHT_BUTTON   = 2;

        // Mouse button state
        public const int DOWN           = 0;
        public const int UP             = 1;

        // glutGet parameters
        public const int ELAPSED_TIME   = 0x02BC;
        public const int WINDOW_WIDTH   = 0x0066;
        public const int WINDOW_HEIGHT  = 0x0067;

#if __LINUX__
        private const string LIB_GLUT = "libglut.so.3"; // "/usr/lib64/libglut.so.3"

        [DllImport(LIB_GLUT, EntryPoint="glutInit", CallingConvention=CallingConvention.Cdecl)]
        public static extern void Init(ref int argcp, string[] argv);

        [DllImport(LIB_GLUT, EntryPoint="glutInitDisplayMode", CallingConvention=CallingConvention.Cdecl)]
        public static extern void InitDisplayMode(int argcp);

        [DllImport(LIB_GLUT, EntryPoint="glutInitWindowSize", CallingConvention=CallingConvention.Cdecl)]
        public static extern void InitWindowSize(int width, int height);

        [DllImport(LIB_GLUT, EntryPoint="glutDisplayFunc", CallingConvention=CallingConvention.Cdecl)]
        public static extern void SetDisplayFunc(DisplayFunc func);

        [DllImport(LIB_GLUT, EntryPoint = "glutReshapeFunc", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetReshapeFunc(ReshapeFunc func);

        [DllImport(LIB_GLUT, EntryPoint="glutPassiveMotionFunc", CallingConvention=CallingConvention.Cdecl)]
        public static extern void SetPassiveMotionFunc(PassiveMotionFunc func);

        [DllImport(LIB_GLUT, EntryPoint="glutMouseFunc", CallingConvention=CallingConvention.Cdecl)]
        public static extern void SetMouseFunc(MouseFunc func);

        [DllImport(LIB_GLUT, EntryPoint="glutCreateWindow", CallingConvention=CallingConvention.Cdecl)]
        public static extern int CreateWindow(string title);

        [DllImport(LIB_GLUT, EntryPoint="glutMainLoop", CallingConvention=CallingConvention.Cdecl)]
        public static extern void MainLoop();

        [DllImport(LIB_GLUT, EntryPoint="glutSwapBuffers", CallingConvention=CallingConvention.Cdecl)]
        public static extern void SwapBuffers();

        [DllImport(LIB_GLUT, EntryPoint="glutPostRedisplay", CallingConvention=CallingConvention.Cdecl)]
        public static extern void PostRedisplay();

        [DllImport(LIB_GLUT, EntryPoint="glutGet", CallingConvention=CallingConvention.Cdecl)]
        public static extern int Get(int state);

#else
        public static void Init(ref int argcp, string[] argv)
        {
            _start = DateTime.Now;
        }

        public static void InitDisplayMode(int argcp)
        {
        }

        public static void InitWindowSize(int width, int height)
        {
            _width = width;
            _height = height;
        }

        public static void SetDisplayFunc(DisplayFunc func)
        {
            _displayFunc = func;
        }

        public static void SetReshapeFunc(ReshapeFunc func)
        {
            _reshapeFunc = func;
        }

        public static void SetPassiveMotionFunc(PassiveMotionFunc func)
        {
            _passiveMotionFunc = func;
        }

        public static void SetMouseFunc(MouseFunc func)
        {
            _mouseFunc = func;
        }

        public static int CreateWindow(string title)
        {
            // Window class
            WindowClassEx windowClass = new WindowClassEx
            {
                Size = (uint)Marshal.SizeOf<WindowClassEx>(),
                WindowProc = _wndProc,
                InstanceHandle = GetModuleHandle(null),
                CursorHandle = LoadCursor(IntPtr.Zero, new IntPtr(IDC_ARROW)),
                ClassName = ClassName
            };
            RegisterClassEx(ref windowClass);

            // Window
            Rectangle rect = new Rectangle { Left = 0, Top = 0, Right = _width, Bottom = _height };
            AdjustWindowRect(ref rect, WS_OVERLAPPEDWINDOW, false);
            _hWnd = CreateWindowEx(0, ClassName, title, WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, rect.Right - rect.Left, rect.Bottom - rect.Top,
                IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, IntPtr.Zero);

            // GL Context
            PixelFormatDescriptor pfd = new PixelFormatDescriptor
            {
                Size = (short)Marshal.SizeOf<PixelFormatDescriptor>(),
                Version = 1,
                Flags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                PixelType = PFD_TYPE_RGBA,
                ColorBits = 24,
                StencilBits = 8
            };

            _hDC = GetDC(_hWnd);
            int pixelFormat = ChoosePixelFormat(_hDC, ref pfd);
            SetPixelFormat(_hDC, pixelFormat, ref pfd);

            IntPtr hRC = wglCreateContext(_hDC);
            wglMakeCurrent(_hDC, hRC);

            return 0;
        }

        public static void MainLoop()
        {
            ShowWindow(_hWnd, SW_SHOWNORMAL);

            Message msg;

            do
            {
                if (PeekMessage(out msg, IntPtr.Zero, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(ref msg);
                    DispatchMessage(ref msg);
                }
                else
                {
                    _displayFunc?.Invoke();
                }
            }
            while (msg.message != WM_QUIT);
        }

        public static void SwapBuffers()
        {
            SwapBuffers(_hDC);
        }

        public static void PostRedisplay()
        {
        }

        public static int Get(int state)
        {
            if (state == ELAPSED_TIME)
            {
                return (int)(DateTime.Now - _start).TotalMilliseconds;
            }
            else if (state == WINDOW_WIDTH)
            {
                Rectangle rect;
                GetClientRect(_hWnd, out rect);
                return rect.Right;
            }
            else if (state == WINDOW_HEIGHT)
            {
                Rectangle rect;
                GetClientRect(_hWnd, out rect);
                return rect.Bottom;
            }

            return 0;
        }

        #region Private members
        private static DateTime _start;

        private static int _width;
        private static int _height;

        private static DisplayFunc _displayFunc;
        private static ReshapeFunc _reshapeFunc;
        private static PassiveMotionFunc _passiveMotionFunc;
        private static MouseFunc _mouseFunc;

        private static IntPtr _hWnd;
        private static IntPtr _hDC;
        #endregion

        #region Window Proc
        private static WindowProc _wndProc = WndProc;

        private static IntPtr WndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)
        {
            switch (msg)
            {
                case WM_SIZE:
                {
                    _reshapeFunc?.Invoke(LoWord(lParam), HiWord(lParam));
                    break;
                }
                case WM_LBUTTONUP:
                {
                    _mouseFunc?.Invoke(LEFT_BUTTON, UP, LoWord(lParam), HiWord(lParam));
                    break;
                }
                case WM_LBUTTONDOWN:
                {
                    _mouseFunc?.Invoke(LEFT_BUTTON, DOWN, LoWord(lParam), HiWord(lParam));
                    break;
                }
                case WM_MOUSEMOVE:
                {
                    _passiveMotionFunc?.Invoke(LoWord(lParam), HiWord(lParam));
                    break;
                }
                case WM_DESTROY:
                {
                    PostQuitMessage(0);
                    return IntPtr.Zero;
                }
            }

            return DefWindowProc(hWnd, msg, wParam, lParam);
        }

        private static int LoWord(IntPtr n)
        {
            return (short)((unchecked((int)(long)n)) & 0xffff);
        }
        private static int HiWord(IntPtr n)
        {
            return (short)(((unchecked((int)(long)n)) >> 16) & 0xffff);
        }
        #endregion

        #region Constants
        private const string ClassName = "GLUT_Window";

        private const int IDC_ARROW = 32512;

        private const int CW_USEDEFAULT = unchecked((int)0x80000000);

        private const int WS_BORDER             = 0x00800000;
        private const int WS_CAPTION            = 0x00C00000;
        private const int WS_MAXIMIZEBOX        = 0x00010000;
        private const int WS_MINIMIZEBOX        = 0x00020000;
        private const int WS_OVERLAPPED         = 0x00000000;
        private const int WS_SYSMENU            = 0x00080000;
        private const int WS_THICKFRAME         = 0x00040000;
        private const int WS_OVERLAPPEDWINDOW   = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

        private const int PFD_DOUBLEBUFFER          = 0x00000001;
        private const int PFD_DRAW_TO_WINDOW        = 0x00000004;
        private const int PFD_SUPPORT_OPENGL        = 0x00000020;
        private const int PFD_TYPE_RGBA             = 0;

        private const int SW_SHOWNORMAL = 1;

        private const uint WM_DESTROY = 0x0002;
        private const uint WM_SIZE = 0x0005;
        private const uint WM_MOUSEMOVE = 0x0200;
        private const uint WM_LBUTTONDOWN = 0x0201;
        private const uint WM_LBUTTONUP = 0x0202;
        private const uint WM_QUIT = 0x0012;

        private const int PM_REMOVE = 0x0001;
        #endregion

        #region Types
        private delegate IntPtr WindowProc(IntPtr hwnd, uint msg, IntPtr wParam, IntPtr lParam);

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        private struct WindowClassEx
        {
            public uint Size;
            public int Styles;
            [MarshalAs(UnmanagedType.FunctionPtr)]
            public WindowProc WindowProc;
            public int ClassExtraBytes;
            public int WindowExtraBytes;
            public IntPtr InstanceHandle;
            public IntPtr IconHandle;
            public IntPtr CursorHandle;
            public IntPtr BackgroundBrushHandle;
            public string MenuName;
            public string ClassName;
            public IntPtr SmallIconHandle;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr WindowHandle;
            public uint message;
            public IntPtr wParam;
            public IntPtr lParam;
            public int time;
            public Point point;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Point
        {
            public int X;
            public int Y;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        private struct Rectangle
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        private struct PixelFormatDescriptor
        {
            public short Size;
            public short Version;
            public int Flags;
            public byte PixelType;
            public byte ColorBits;
            public byte RedBits;
            public byte RedShift;
            public byte GreenBits;
            public byte GreenShift;
            public byte BlueBits;
            public byte BlueShift;
            public byte AlphaBits;
            public byte AlphaShift;
            public byte AccumBits;
            public byte AccumRedBits;
            public byte AccumGreenBits;
            public byte AccumBlueBits;
            public byte AccumAlphaBits;
            public byte DepthBits;
            public byte StencilBits;
            public byte AuxBuffers;
            public byte LayerType;
            public byte Reserved;
            public int LayerMask;
            public int VisibleMask;
            public int DamageMask;
        }

        #endregion

        #region Imports
        [DllImport("kernel32", CharSet = CharSet.Auto)]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern ushort RegisterClassEx([In] ref WindowClassEx lpwcx);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern IntPtr LoadCursor(IntPtr hInstance, IntPtr lpCursorResource);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern bool AdjustWindowRect(ref Rectangle lpRect, int dwStyle, bool bMenu);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern IntPtr CreateWindowEx(int dwExStyle, string lpClassName,
            string lpWindowName, int dwStyle, int x, int y, int nWidth, int nHeight,
            IntPtr hwndParent, IntPtr hMenu, IntPtr hInstance, IntPtr lpParam);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern IntPtr GetDC(IntPtr hWnd);

        [DllImport("user32", CharSet = CharSet.Auto, ExactSpelling = true)]
        private static extern bool ShowWindow(IntPtr hwnd, int nCmdShow);

        [DllImport("user32", CharSet = CharSet.Auto, ExactSpelling = true)]
        private static extern bool GetClientRect(IntPtr hwnd, out Rectangle lpRect);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern IntPtr DefWindowProc(IntPtr hwnd, uint uMsg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern bool PeekMessage(out Message lpMsg, IntPtr hWnd, uint wMsgFilterMin,
            uint wMsgFilterMax, uint wRemoveMsg);

        [DllImport("user32", CharSet = CharSet.Auto, ExactSpelling = true)]
        private static extern bool TranslateMessage([In] ref Message lpMsg);

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern IntPtr DispatchMessage([In] ref Message lpMsg);

        [DllImport("user32", CharSet = CharSet.Auto, ExactSpelling = true)]
        private static extern void PostQuitMessage(int nExitCode);

        [DllImport("gdi32", CharSet = CharSet.Auto)]
        private static extern int ChoosePixelFormat(IntPtr hdc, [In] ref PixelFormatDescriptor ppfd);

        [DllImport("gdi32", CharSet = CharSet.Auto)]
        private static extern bool SetPixelFormat(IntPtr hdc, int format, ref PixelFormatDescriptor ppfd);

        [DllImport("gdi32", CharSet = CharSet.Auto)]
        private static extern bool SwapBuffers(IntPtr hdc);

        [DllImport("opengl32")]
        private static extern IntPtr wglCreateContext(IntPtr hdc);

        [DllImport("opengl32")]
        private static extern bool wglMakeCurrent(IntPtr hdc, IntPtr hglrc);
        #endregion
#endif
    }
}
