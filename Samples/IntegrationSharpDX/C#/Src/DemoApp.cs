namespace IntegrationSharpDX
{
    #region

    using System;
    using System.Drawing;
    using System.Windows.Forms;
    using global::SharpDX.Windows;

    #endregion

    /// <summary>
    /// Root clas for a Demo Application
    /// </summary>
    public abstract class DemoApp
    {
        private readonly DemoTime clock = new DemoTime();

        private FormWindowState currentFormWindowState;

        protected DemoConfiguration demoConfiguration;

        private bool disposed;

        protected Form form { get; private set; }

        private float frameAccumulator;

        private int frameCount;

        /// <summary>
        /// Performs object finalization.
        /// </summary>
        ~DemoApp()
        {
            if (!this.disposed)
            {
                this.Dispose(false);
                this.disposed = true;
            }
        }

        /// <summary>
        /// Gets the config.
        /// </summary>
        /// <value>The config.</value>
        public DemoConfiguration Config
        {
            get { return this.demoConfiguration; }
        }

        /// <summary>
        /// Gets the number of seconds passed since the last frame.
        /// </summary>
        public float FrameDelta { get; private set; }

        /// <summary>
        /// Gets the number of seconds passed since the last frame.
        /// </summary>
        public float FramePerSecond { get; private set; }

        /// <summary>
        /// Return the Handle to display to.
        /// </summary>
        protected IntPtr DisplayHandle
        {
            get { return this.form.Handle; }
        }

        protected Size RenderingSize
        {
            get { return this.form.ClientSize; }
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        public void Dispose()
        {
            if (!this.disposed)
            {
                this.Dispose(true);
                this.disposed = true;
            }
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Quits the sample.
        /// </summary>
        public void Exit()
        {
            this.form.Close();
        }

        /// <summary>
        /// Runs the demo with default presentation
        /// </summary>
        public void Run()
        {
            this.Run(new DemoConfiguration());
        }

        /// <summary>
        /// Runs the demo.
        /// </summary>
        public void Run(DemoConfiguration demoConfiguration)
        {
            this.demoConfiguration = demoConfiguration ?? new DemoConfiguration();
            this.form = this.CreateForm(this.demoConfiguration);
            this.Initialize(this.demoConfiguration);

            var isFormClosed = false;
            var formIsResizing = false;

            this.form.MouseClick += this.HandleMouseClick;
            this.form.KeyDown += this.HandleKeyDown;
            this.form.KeyUp += this.HandleKeyUp;
            this.form.Resize += (o, args) =>
                                 {
                                     if (this.form.WindowState != this.currentFormWindowState)
                                     {
                                         this.HandleResize(o, args);
                                     }

                                     this.currentFormWindowState = this.form.WindowState;
                                 };

            this.form.ResizeBegin += (o, args) => { formIsResizing = true; };
            this.form.ResizeEnd += (o, args) =>
                                    {
                                        formIsResizing = false;
                                        this.HandleResize(o, args);
                                    };

            this.form.Closed += (o, args) => { isFormClosed = true; };

            this.LoadContent();

            this.clock.Start();
            this.BeginRun();
            RenderLoop.Run(
                this.form,
                () =>
                {
                    if (isFormClosed)
                    {
                        return;
                    }

                    this.OnUpdate();
                    if (!formIsResizing)
                        this.Render();
                });

            this.UnloadContent();
            this.EndRun();

            // Dispose explicity
            this.Dispose();
        }

        /// <summary>
        /// In a derived class, implements logic that should occur before all
        /// other rendering.
        /// </summary>
        protected virtual void BeginDraw()
        {
        }

        protected virtual void BeginRun()
        {
        }

        /// <summary>
        /// Create Form for this demo.
        /// </summary>
        /// <param name="config"></param>
        /// <returns></returns>
        protected virtual Form CreateForm(DemoConfiguration config)
        {
            return new RenderForm(config.Title)
            {
                ClientSize = new Size(config.Width, config.Height)
            };
        }

        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        /// <param name="disposeManagedResources">
        /// If true, managed resources should be
        /// disposed of in addition to unmanaged resources.
        /// </param>
        protected virtual void Dispose(bool disposeManagedResources)
        {
            if (disposeManagedResources)
            {
                if (this.form != null)
                    this.form.Dispose();
            }
        }

        /// <summary>
        /// In a derived class, implements logic to render the sample.
        /// </summary>
        protected virtual void Draw(DemoTime time)
        {
        }

        /// <summary>
        /// In a derived class, implements logic that should occur after all
        /// other rendering.
        /// </summary>
        protected virtual void EndDraw()
        {
        }

        protected virtual void EndRun()
        {
        }

        /// <summary>
        /// In a derived class, implements logic to initialize the sample.
        /// </summary>
        protected abstract void Initialize(DemoConfiguration demoConfiguration);

        protected virtual void KeyDown(KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                this.Exit();
        }

        protected virtual void KeyUp(KeyEventArgs e)
        {
        }

        protected virtual void LoadContent()
        {
        }

        protected virtual void MouseClick(MouseEventArgs e)
        {
        }

        protected virtual void UnloadContent()
        {
        }

        /// <summary>
        /// In a derived class, implements logic to update any relevant sample state.
        /// </summary>
        protected virtual void Update(DemoTime time)
        {
        }

        /// <summary>
        /// Handles a key down event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs" /> instance containing the event data.</param>
        private void HandleKeyDown(object sender, KeyEventArgs e)
        {
            this.KeyDown(e);
        }

        /// <summary>
        /// Handles a key up event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs" /> instance containing the event data.</param>
        private void HandleKeyUp(object sender, KeyEventArgs e)
        {
            this.KeyUp(e);
        }

        /// <summary>
        /// Handles a mouse click event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs" /> instance containing the event data.</param>
        private void HandleMouseClick(object sender, MouseEventArgs e)
        {
            this.MouseClick(e);
        }

        protected virtual void HandleResize(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// Updates sample state.
        /// </summary>
        private void OnUpdate()
        {
            this.FrameDelta = (float)this.clock.Update();
            this.Update(this.clock);
        }

        /// <summary>
        /// Renders the sample.
        /// </summary>
        private void Render()
        {
            this.frameAccumulator += this.FrameDelta;
            ++this.frameCount;
            if (this.frameAccumulator >= 1.0f)
            {
                this.FramePerSecond = this.frameCount / this.frameAccumulator;

                this.form.Text = this.demoConfiguration.Title + " - FPS: " + this.FramePerSecond;
                this.frameAccumulator = 0.0f;
                this.frameCount = 0;
            }

            this.BeginDraw();
            this.Draw(this.clock);
            this.EndDraw();
        }
    }
}