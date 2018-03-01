namespace IntegrationSharpDX
{
    #region

    using System;
    using System.Windows.Forms;
    using global::SharpDX;
    using global::SharpDX.Direct3D;
    using global::SharpDX.Direct3D11;
    using global::SharpDX.DXGI;
    using Device = global::SharpDX.Direct3D11.Device;
    using Resource = global::SharpDX.Direct3D11.Resource;

    #endregion

    /// <summary>
    /// Root class for Direct3D11 Demo App
    /// </summary>
    public class DemoAppD3D11 : DemoApp
    {
        private Texture2D backBuffer;
        private Texture2D stencilBuffer;

        private RenderTargetView backBufferView;
        private DepthStencilView stencilBufferView;

        private Device device;

        private SwapChain swapChain;

        /// <summary>
        /// Returns the backbuffer used by the SwapChain
        /// </summary>
        public Texture2D BackBuffer => this.backBuffer;

        /// <summary>
        /// Returns the stencil buffer used by the SwapChain
        /// </summary>
        public Texture2D StencilBuffer => this.stencilBuffer;

        /// <summary>
        /// Returns the render target view on the backbuffer used by the SwapChain.
        /// </summary>
        public RenderTargetView BackBufferView => this.backBufferView;

        /// <summary>
        /// Returns the stencil view on the stencil buffer used by the SwapChain.
        /// </summary>
        public DepthStencilView StencilBufferView  => this.stencilBufferView;

        /// <summary>
        /// Returns the device
        /// </summary>
        public Device Device => this.device;

        public SwapChain SwapChain => this.swapChain;

        protected override void BeginDraw()
        {
            base.BeginDraw();
            this.Device.ImmediateContext.Rasterizer.SetViewport(new Viewport(0, 0, this.Config.Width, this.Config.Height));
            this.Device.ImmediateContext.OutputMerger.SetTargets(this.stencilBufferView, this.backBufferView);
        }

        protected override void EndDraw()
        {
            this.swapChain.Present(this.Config.WaitVerticalBlanking ? 1 : 0, PresentFlags.None);
        }

        protected override void Initialize(DemoConfiguration demoConfiguration)
        {
            // SwapChain description
            var desc = new SwapChainDescription()
            {
                BufferCount = 1,
                ModeDescription = new ModeDescription(
                    demoConfiguration.Width,
                    demoConfiguration.Height,
                    new Rational(60, 1),
                    Format.R8G8B8A8_UNorm),
                IsWindowed = true,
                OutputHandle = this.DisplayHandle,
                SampleDescription = new SampleDescription(1, 0),
                SwapEffect = SwapEffect.Discard,
                Usage = Usage.RenderTargetOutput
            };

            // Create Device and SwapChain
            FeatureLevel featureLevel = new Device(DriverType.Hardware).FeatureLevel;
            if (featureLevel > FeatureLevel.Level_11_0)
            {
                featureLevel = FeatureLevel.Level_11_0;
            }

            Device.CreateWithSwapChain(
                DriverType.Hardware,
                DeviceCreationFlags.BgraSupport | DeviceCreationFlags.Debug,
                new[] { featureLevel },
                desc,
                out this.device,
                out this.swapChain);

            // Ignore all windows events
            var factory = this.swapChain.GetParent<Factory>();
            factory.MakeWindowAssociation(this.DisplayHandle, WindowAssociationFlags.IgnoreAll);

            this.CreateBackBuffer();
            this.CreateStencilBuffer();
        }

        protected override void HandleResize(object sender, EventArgs e)
        {
            if (this.form.WindowState == FormWindowState.Minimized)
            {
                return;
            }

            var size = this.RenderingSize;

            if (this.demoConfiguration.Width == size.Width
                && this.demoConfiguration.Height == size.Height)
            {
                return;
            }

            device.ImmediateContext.ClearState();
            this.DestroyBackBuffer();
            this.DestroyStencilBuffer();

            var desc = this.SwapChain.Description;
            this.SwapChain.ResizeBuffers(desc.BufferCount, size.Width, size.Height, Format.Unknown, SwapChainFlags.AllowModeSwitch);

            demoConfiguration.Width = size.Width;
            demoConfiguration.Height = size.Height;

            this.CreateBackBuffer();
            this.CreateStencilBuffer();
        }

        private void DestroyBackBuffer()
        {
            this.backBufferView.Dispose();
            this.backBuffer.Dispose();
        }

        private void CreateBackBuffer()
        {
            this.backBuffer = Resource.FromSwapChain<Texture2D>(this.swapChain, 0);
            this.backBufferView = new RenderTargetView(this.device, this.backBuffer);
        }

        private void DestroyStencilBuffer()
        {
            this.stencilBufferView.Dispose();
            this.stencilBuffer.Dispose();
        }

        private void CreateStencilBuffer()
        {
            this.stencilBuffer = new Texture2D(device, new Texture2DDescription()
            {
                Format = Format.D32_Float_S8X24_UInt,
                ArraySize = 1,
                MipLevels = 1,
                Width = demoConfiguration.Width,
                Height = demoConfiguration.Height,
                SampleDescription = new SampleDescription(1, 0),
                Usage = ResourceUsage.Default,
                BindFlags = BindFlags.DepthStencil,
                CpuAccessFlags = CpuAccessFlags.None,
                OptionFlags = ResourceOptionFlags.None
            });
            this.stencilBufferView = new DepthStencilView(this.device, this.stencilBuffer);
        }
    }
}