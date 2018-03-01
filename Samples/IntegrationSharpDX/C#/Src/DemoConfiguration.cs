namespace IntegrationSharpDX
{
    public class DemoConfiguration
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="DemoConfiguration" /> class.
        /// </summary>
        public DemoConfiguration() : this("SharpDX Demo")
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DemoConfiguration" /> class.
        /// </summary>
        public DemoConfiguration(string title) : this(title, 800, 600)
        {
        }

        public DemoConfiguration(string title, int width, int height)
        {
            this.Title = title;
            this.Width = width;
            this.Height = height;
            this.WaitVerticalBlanking = false;
        }

        /// <summary>
        /// Gets or sets the height of the window.
        /// </summary>
        public int Height { get; set; }

        /// <summary>
        /// Gets or sets the window title.
        /// </summary>
        public string Title { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [wait vertical blanking].
        /// </summary>
        /// <value>
        /// <c>true</c> if [wait vertical blanking]; otherwise, <c>false</c>.
        /// </value>
        public bool WaitVerticalBlanking { get; set; }

        /// <summary>
        /// Gets or sets the width of the window.
        /// </summary>
        public int Width { get; set; }
    }
}