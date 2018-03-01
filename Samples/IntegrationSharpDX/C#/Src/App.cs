namespace IntegrationSharpDX
{
    #region

    using System;
    using System.Drawing;
    using System.Windows.Forms;
    using global::SharpDX.Direct3D11;
    using global::SharpDX.Mathematics.Interop;

    #endregion

    public class App : DemoAppD3D11
    {
        private static readonly RawColor4 BackgroundColor = new RawColor4(0, 0, 0, 1);

        private Action contentLoadCallback;

        public event Action Close;

        public event Action<KeyEventArgs> KeyDownEvent;

        public event Action<KeyPressEventArgs> KeyPressEvent;

        public event Action<KeyEventArgs> KeyUpEvent;

        public event Action<MouseEventArgs> MouseDown;

        public event Action<MouseEventArgs> MouseMove;

        public event Action<MouseEventArgs> MouseUp;

        public event Action PostRender;

        public event Action PreRender;

        public event Action<int, int> Resize;

        public event Action<double> Tick;

        public Size Size => this.form.ClientSize;

        public void Run(DemoConfiguration appConfiguration, Action contentLoadCallback)
        {
            this.contentLoadCallback = contentLoadCallback;
            this.Run(appConfiguration);
        }

        protected override void BeginDraw()
        {
            base.BeginDraw();
            this.PreRender?.Invoke();
        }

        protected override void EndDraw()
        {
            base.EndDraw();
            this.Device.ImmediateContext.ClearRenderTargetView(this.BackBufferView, BackgroundColor);
            this.Device.ImmediateContext.ClearDepthStencilView(this.StencilBufferView, DepthStencilClearFlags.Stencil, 0.0f, 0);
            this.PostRender?.Invoke();
        }

        protected override void Initialize(DemoConfiguration demoConfiguration)
        {
            base.Initialize(demoConfiguration);

            this.form.Closing += (s, e) => this.Close?.Invoke();
            this.form.ClientSizeChanged += this.FormSizeChangedHandler;
            this.form.MouseMove += this.FormMouseMoveHandler;
            this.form.MouseDown += this.FormMouseDownHandler;
            this.form.MouseUp += this.FormMouseUpHandler;
            this.form.KeyPress += this.FormKeyPressHandler;
        }

        protected override void KeyDown(KeyEventArgs e)
        {
            base.KeyDown(e);
            this.KeyDownEvent?.Invoke(e);
        }

        protected override void KeyUp(KeyEventArgs e)
        {
            base.KeyUp(e);
            this.KeyUpEvent?.Invoke(e);
        }

        protected override void LoadContent()
        {
            base.LoadContent();
            this.contentLoadCallback();
        }

        protected override void Update(DemoTime time)
        {
            base.Update(time);
            this.Tick?.Invoke(time.ElapseTime);
        }

        private void FormKeyPressHandler(object sender, KeyPressEventArgs e)
        {
            this.KeyPressEvent?.Invoke(e);
        }

        private void FormMouseDownHandler(object sender, MouseEventArgs e)
        {
            this.MouseDown?.Invoke(e);
        }

        private void FormMouseMoveHandler(object sender, MouseEventArgs e)
        {
            this.MouseMove?.Invoke(e);
        }

        private void FormMouseUpHandler(object sender, MouseEventArgs e)
        {
            this.MouseUp?.Invoke(e);
        }

        private void FormSizeChangedHandler(object sender, EventArgs e)
        {
            var size = this.form.ClientSize;
            this.Resize?.Invoke(size.Width, size.Height);
        }
    }
}