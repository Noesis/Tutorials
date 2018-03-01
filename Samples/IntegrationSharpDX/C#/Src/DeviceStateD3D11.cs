namespace IntegrationSharpDX
{
    #region

    using global::SharpDX;
    using global::SharpDX.Direct3D;
    using global::SharpDX.Direct3D11;
    using global::SharpDX.DXGI;
    using global::SharpDX.Mathematics.Interop;

    #endregion

    /// <summary>
    /// This helper provide methods for saving and restoring DX11 graphics device state
    /// with MonoGame. Provided by NoesisGUI team.
    /// </summary>
    internal class DeviceStateD3D11
    {
        private RawColor4 blendFactor;

        private BlendState blendState;

        private DepthStencilState depthState;

        private DepthStencilView depthStencilView;

        private Buffer ib;

        private Format ibFormat;

        private int ibOffset;

        private InputLayout layout;

        private PixelShader ps;

        private Buffer[] psConstantBuffers;

        private ShaderResourceView[] psResources;

        private SamplerState[] psSamplers;

        private RasterizerState rasterizerState;

        private RenderTargetView[] renderTargetView;

        private int sampleMaskRef;

        private Rectangle[] scissorRectangles;

        private int stencilRefRef;

        private PrimitiveTopology topology;

        private Buffer[] vb = new Buffer[1];

        private int[] vbOffset = new int[1];

        private int[] vbStride = new int[1];

        private RawViewportF[] viewports;

        private VertexShader vs;

        private Buffer[] vsConstantBuffers;

        private ShaderResourceView[] vsResources;

        private SamplerState[] vsSamplers;

        public void Restore(DeviceContext context)
        {
            context.InputAssembler.PrimitiveTopology = this.topology;
            context.InputAssembler.InputLayout = this.layout;
            context.Rasterizer.SetViewports(this.viewports);
            context.Rasterizer.State = this.rasterizerState;
            if (this.rasterizerState != null
                && this.rasterizerState.Description.IsScissorEnabled)
            {
                context.Rasterizer.SetScissorRectangles(this.scissorRectangles);
            }

            context.OutputMerger.SetBlendState(this.blendState, this.blendFactor, this.sampleMaskRef);
            context.OutputMerger.SetDepthStencilState(this.depthState, this.stencilRefRef);
            context.OutputMerger.SetRenderTargets(this.depthStencilView, this.renderTargetView[0]);

            context.PixelShader.Set(this.ps);
            context.PixelShader.SetConstantBuffers(0, this.psConstantBuffers);
            context.PixelShader.SetSamplers(0, this.psSamplers);
            context.PixelShader.SetShaderResources(0, this.psResources);

            context.VertexShader.Set(this.vs);
            context.VertexShader.SetConstantBuffers(0, this.vsConstantBuffers);
            context.VertexShader.SetSamplers(0, this.vsSamplers);
            context.VertexShader.SetShaderResources(0, this.vsResources);

            context.InputAssembler.SetIndexBuffer(this.ib, this.ibFormat, this.ibOffset);
            context.InputAssembler.SetVertexBuffers(0, this.vb, this.vbStride, this.vbOffset);

            if (this.renderTargetView[0] != null)
            {
                this.renderTargetView[0].Dispose();
            }

            this.depthStencilView?.Dispose();
        }

        public void Save(DeviceContext context)
        {
            this.topology = context.InputAssembler.PrimitiveTopology;
            this.layout = context.InputAssembler.InputLayout;
            this.viewports = context.Rasterizer.GetViewports<RawViewportF>();
            this.rasterizerState = context.Rasterizer.State;
            if (this.rasterizerState != null
                && this.rasterizerState.Description.IsScissorEnabled)
            {
                this.scissorRectangles = context.Rasterizer.GetScissorRectangles<Rectangle>();
            }
            this.blendState = context.OutputMerger.GetBlendState(out this.blendFactor, out this.sampleMaskRef);
            this.depthState = context.OutputMerger.GetDepthStencilState(out this.stencilRefRef);
            this.renderTargetView = context.OutputMerger.GetRenderTargets(1, out this.depthStencilView);

            this.ps = context.PixelShader.Get();
            this.psConstantBuffers = context.PixelShader.GetConstantBuffers(0, 4);
            this.psSamplers = context.PixelShader.GetSamplers(0, 4);
            this.psResources = context.PixelShader.GetShaderResources(0, 4);

            this.vs = context.VertexShader.Get();
            this.vsConstantBuffers = context.VertexShader.GetConstantBuffers(0, 4);
            this.vsSamplers = context.VertexShader.GetSamplers(0, 4);
            this.vsResources = context.VertexShader.GetShaderResources(0, 4);

            context.InputAssembler.GetIndexBuffer(out this.ib, out this.ibFormat, out this.ibOffset);
            context.InputAssembler.GetVertexBuffers(0, 1, this.vb, this.vbStride, this.vbOffset);
        }
    }
}