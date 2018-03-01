using System;
using System.Runtime.InteropServices;

namespace IntegrationGLUT
{
    public static class GLUTWrapper
    {
        public static void Init(int width, int height, string title)
        {
            GLUT_Init(width, height, title);

            //GLUT_RegisterClose(_CloseCallback);
            GLUT_RegisterTick(_TickCallback);
            GLUT_RegisterPreRender(_PreRenderCallback);
            GLUT_RegisterPostRender(_PostRenderCallback);
            GLUT_RegisterResize(_ResizeCallback);
            GLUT_RegisterMouse(_MouseMoveCallback, _MouseDownCallback, _MouseUpCallback);
            GLUT_RegisterKeyboard(_KeyDownCallback, _KeyUpCallback);

            _startTime = DateTime.Now;
        }

        public static void Shutdown()
        {
            //GLUT_RegisterClose(null);
            GLUT_RegisterTick(null);
            GLUT_RegisterPreRender(null);
            GLUT_RegisterPostRender(null);
            GLUT_RegisterResize(null);
            GLUT_RegisterMouse(null, null, null);
            GLUT_RegisterKeyboard(null, null);
        }

        public static void Run()
        {
            GLUT_Run();
        }

        #region Public Events
        public delegate void CloseEventHandler();
        public static event CloseEventHandler Close;

        public delegate void TickEventHandler(double timeInSeconds);
        public static event TickEventHandler Tick;

        public delegate void RenderEventHandler();
        public static event RenderEventHandler PreRender;
        public static event RenderEventHandler PostRender;

        public delegate void ResizeEventHandler(int width, int height);
        public static event ResizeEventHandler Resize;

        public delegate void MouseMoveEventHandler(int x, int y);
        public static event MouseMoveEventHandler MouseMove;

        public enum MouseButton
        {
            Left,
            Right,
            Middle
        }

        public delegate void MouseButtonEventHandler(int x, int y, MouseButton button);
        public static event MouseButtonEventHandler MouseDown;
        public static event MouseButtonEventHandler MouseUp;

        public enum SpecialKey
        {
            None,
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
            PageUp, PageDown,
            Home, End, Insert,
            Left, Right, Up, Down
        };

        [Flags]
        public enum ModifierKey
        {
            Shift = 1,
            Ctrl = 2,
            Alt = 4
        }

        public delegate void KeyEventHandler(char key, SpecialKey specialKey, ModifierKey modifiers);
        public static event KeyEventHandler KeyDown;
        public static event KeyEventHandler KeyUp;
        #endregion

        #region Private members
        static DateTime _startTime;
        #endregion

        #region Imports
        [DllImport("GLUTWrapper", EntryPoint = "GLUT_Init")]
        static extern void GLUT_Init(int width, int height, [MarshalAs(UnmanagedType.LPStr)] string title);

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_RegisterClose")]
        static extern void GLUT_RegisterClose(CloseCallback tickCallback);
        delegate void CloseCallback();
        static CloseCallback _CloseCallback = OnClose;
        static void OnClose()
        {
            CloseEventHandler handler = Close;
            if (handler != null)
            {
                handler();
            }
        }

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_RegisterTick")]
        static extern void GLUT_RegisterTick(TickCallback tickCallback);
        delegate void TickCallback();
        static TickCallback _TickCallback = OnTick;
        static void OnTick()
        {
            TickEventHandler handler = Tick;
            if (handler != null)
            {
                handler((DateTime.Now - _startTime).TotalSeconds);
            }
        }

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_RegisterPreRender")]
        static extern void GLUT_RegisterPreRender(PreRenderCallback renderCallback);
        delegate void PreRenderCallback();
        static PreRenderCallback _PreRenderCallback = OnPreRender;
        static void OnPreRender()
        {
            RenderEventHandler handler = PreRender;
            if (handler != null)
            {
                handler();
            }
        }

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_RegisterPostRender")]
        static extern void GLUT_RegisterPostRender(PostRenderCallback renderCallback);
        delegate void PostRenderCallback();
        static PostRenderCallback _PostRenderCallback = OnPostRender;
        static void OnPostRender()
        {
            RenderEventHandler handler = PostRender;
            if (handler != null)
            {
                handler();
            }
        }

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_RegisterResize")]
        static extern void GLUT_RegisterResize(ResizeCallback resizeCallback);
        delegate void ResizeCallback(int width, int height);
        static ResizeCallback _ResizeCallback = OnResize;
        static void OnResize(int width, int height)
        {
            ResizeEventHandler handler = Resize;
            if (handler != null)
            {
                handler(width, height);
            }
        }

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_RegisterMouse")]
        static extern void GLUT_RegisterMouse(
            MouseMoveCallback mouseMoveCallback,
            MouseButtonCallback mouseDownCallback,
            MouseButtonCallback mouseUpCallback);
        delegate void MouseMoveCallback(int x, int y);
        delegate void MouseButtonCallback(int x, int y, int button);
        static MouseMoveCallback _MouseMoveCallback = OnMouseMove;
        static void OnMouseMove(int x, int y)
        {
            MouseMoveEventHandler handler = MouseMove;
            if (handler != null)
            {
                handler(x, y);
            }
        }
        static MouseButtonCallback _MouseDownCallback = OnMouseDown;
        static void OnMouseDown(int x, int y, int button)
        {
            MouseButtonEventHandler handler = MouseDown;
            if (handler != null)
            {
                handler(x, y, (MouseButton)button);
            }
        }
        static MouseButtonCallback _MouseUpCallback = OnMouseUp;
        static void OnMouseUp(int x, int y, int button)
        {
            MouseButtonEventHandler handler = MouseUp;
            if (handler != null)
            {
                handler(x, y, (MouseButton)button);
            }
        }

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_RegisterKeyboard")]
        static extern void GLUT_RegisterKeyboard(
            KeyboardCallback keyDownCallback,
            KeyboardCallback keyUpCallback);
        delegate void KeyboardCallback(char key, int specialKey, int modifiers);
        static KeyboardCallback _KeyDownCallback = OnKeyDown;
        static void OnKeyDown(char key, int specialKey, int modifiers)
        {
            KeyEventHandler handler = KeyDown;
            if (handler != null)
            {
                handler(key, (SpecialKey)specialKey, (ModifierKey)modifiers);
            }
        }
        static KeyboardCallback _KeyUpCallback = OnKeyUp;
        static void OnKeyUp(char key, int specialKey, int modifiers)
        {
            KeyEventHandler handler = KeyUp;
            if (handler != null)
            {
                handler(key, (SpecialKey)specialKey, (ModifierKey)modifiers);
            }
        }

        [DllImport("GLUTWrapper", EntryPoint = "GLUT_Run")]
        static extern void GLUT_Run();

        #endregion Imports
    }
}
