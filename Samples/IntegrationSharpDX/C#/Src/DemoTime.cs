namespace IntegrationSharpDX
{
    #region

    using System.Diagnostics;

    #endregion

    public class DemoTime
    {
        private readonly Stopwatch stopwatch;

        private double lastUpdate;

        public DemoTime()
        {
            this.stopwatch = new Stopwatch();
        }

        public double ElapseTime => this.stopwatch.ElapsedMilliseconds * 0.001;

        public void Start()
        {
            this.stopwatch.Start();
            this.lastUpdate = 0;
        }

        public void Stop()
        {
            this.stopwatch.Stop();
        }

        public double Update()
        {
            var now = this.ElapseTime;
            var updateTime = now - this.lastUpdate;
            this.lastUpdate = now;
            return updateTime;
        }
    }
}