using System;
using System.Runtime.InteropServices;

namespace IntegrationGLUT
{
    public static class GL
    {
        public const uint FRAMEBUFFER           = 0x8D40;

        public const uint COLOR_BUFFER_BIT      = 0x00004000;
        public const uint STENCIL_BUFFER_BIT    = 0x00000400;

#if __LINUX__
        private const string LIB_GL = "libGL.so"; // "/usr/lib64/libGL.so"

        [DllImport(LIB_GL, EntryPoint="glClearColor", CallingConvention=CallingConvention.Cdecl)]
        public static extern void ClearColor(float red, float green, float blue, float alpha);

        [DllImport(LIB_GL, EntryPoint="glClearStencil", CallingConvention=CallingConvention.Cdecl)]
        public static extern void ClearStencil(int s);

        [DllImport(LIB_GL, EntryPoint="glClear", CallingConvention=CallingConvention.Cdecl)]
        public static extern void Clear(uint mask);

        [DllImport(LIB_GL, EntryPoint="glViewport", CallingConvention=CallingConvention.Cdecl)]
        public static extern void Viewport(int x, int y, uint width, uint height);

        [DllImport(LIB_GL, EntryPoint="glBindFramebuffer", CallingConvention=CallingConvention.Cdecl)]
        public static extern void BindFramebuffer(uint target, uint framebuffer);

#else
        static GL()
        {
            _glBindFramebuffer = (BindFramebufferProc)Marshal.GetDelegateForFunctionPointer(
                wglGetProcAddress("glBindFramebuffer"), typeof(BindFramebufferProc));
        }

        public static void BindFramebuffer(uint target, uint framebuffer)
        {
            _glBindFramebuffer(target, framebuffer);
        }

        private delegate void BindFramebufferProc(uint target, uint framebuffer);

        private static BindFramebufferProc _glBindFramebuffer;

        [DllImport("opengl32")]
        private static extern IntPtr wglGetProcAddress([MarshalAs(UnmanagedType.LPStr)] string proc);

        [DllImport("opengl32", EntryPoint = "glClearColor")]
        public static extern void ClearColor(float red, float green, float blue, float alpha);

        [DllImport("opengl32", EntryPoint = "glClearStencil")]
        public static extern void ClearStencil(int s);

        [DllImport("opengl32", EntryPoint = "glClear")]
        public static extern void Clear(uint mask);

        [DllImport("opengl32", EntryPoint = "glViewport")]
        public static extern void Viewport(int x, int y, uint width, uint height);

#endif
    }
}
