#if NOESIS
using Noesis;
#else
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
#endif
using System;

namespace NineSlice
{
    /// <summary>
    /// Nine slice image control
    /// </summary>
    public class NineSliceImage : ContentControl
    {
        public ImageSource ImageSource
        {
            get { return (ImageSource)GetValue(ImageSourceProperty); }
            set { SetValue(ImageSourceProperty, value); }
        }

        public static readonly DependencyProperty ImageSourceProperty = DependencyProperty.Register(
            "ImageSource", typeof(ImageSource), typeof(NineSliceImage),
            new PropertyMetadata(null, OnSlicesChanged));

        public Thickness Slices
        {
            get { return (Thickness)GetValue(SlicesProperty); }
            set { SetValue(SlicesProperty, value); }
        }

        public static readonly DependencyProperty SlicesProperty = DependencyProperty.Register(
            "Slices", typeof(Thickness), typeof(NineSliceImage),
            new PropertyMetadata(new Thickness(), OnSlicesChanged));

        #region 9-grid slices
        public Int32Rect TopLeftViewbox
        {
            get { return (Int32Rect)GetValue(TopLeftViewboxProperty); }
            set { SetValue(TopLeftViewboxProperty, value); }
        }

        public static readonly DependencyProperty TopLeftViewboxProperty = DependencyProperty.Register(
            "TopLeftViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect TopCenterViewbox
        {
            get { return (Int32Rect)GetValue(TopCenterViewboxProperty); }
            set { SetValue(TopCenterViewboxProperty, value); }
        }

        public static readonly DependencyProperty TopCenterViewboxProperty = DependencyProperty.Register(
            "TopCenterViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect TopRightViewbox
        {
            get { return (Int32Rect)GetValue(TopRightViewboxProperty); }
            set { SetValue(TopRightViewboxProperty, value); }
        }

        public static readonly DependencyProperty TopRightViewboxProperty = DependencyProperty.Register(
            "TopRightViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect CenterLeftViewbox
        {
            get { return (Int32Rect)GetValue(CenterLeftViewboxProperty); }
            set { SetValue(CenterLeftViewboxProperty, value); }
        }

        public static readonly DependencyProperty CenterLeftViewboxProperty = DependencyProperty.Register(
            "CenterLeftViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect CenterViewbox
        {
            get { return (Int32Rect)GetValue(CenterViewboxProperty); }
            set { SetValue(CenterViewboxProperty, value); }
        }

        public static readonly DependencyProperty CenterViewboxProperty = DependencyProperty.Register(
            "CenterViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect CenterRightViewbox
        {
            get { return (Int32Rect)GetValue(CenterRightViewboxProperty); }
            set { SetValue(CenterRightViewboxProperty, value); }
        }

        public static readonly DependencyProperty CenterRightViewboxProperty = DependencyProperty.Register(
            "CenterRightViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect BottomLeftViewbox
        {
            get { return (Int32Rect)GetValue(BottomLeftViewboxProperty); }
            set { SetValue(BottomLeftViewboxProperty, value); }
        }

        public static readonly DependencyProperty BottomLeftViewboxProperty = DependencyProperty.Register(
            "BottomLeftViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect BottomCenterViewbox
        {
            get { return (Int32Rect)GetValue(BottomCenterViewboxProperty); }
            set { SetValue(BottomCenterViewboxProperty, value); }
        }

        public static readonly DependencyProperty BottomCenterViewboxProperty = DependencyProperty.Register(
            "BottomCenterViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));

        public Int32Rect BottomRightViewbox
        {
            get { return (Int32Rect)GetValue(BottomRightViewboxProperty); }
            set { SetValue(BottomRightViewboxProperty, value); }
        }

        public static readonly DependencyProperty BottomRightViewboxProperty = DependencyProperty.Register(
            "BottomRightViewbox", typeof(Int32Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Int32Rect()));
        #endregion

        private static void OnSlicesChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NineSliceImage image = (NineSliceImage)d;

            float width = 0.0f;
            float height = 0.0f;

            if (image.ImageSource != null)
            {
                width = (float)image.ImageSource.Width;
                height = (float)image.ImageSource.Height;
            }

            int wl = (int)Math.Min(image.Slices.Left, width);
            int wc = (int)Math.Max(width - image.Slices.Left - image.Slices.Right, 0);
            int wr = (int)Math.Min(image.Slices.Right, width);
            int ht = (int)Math.Min(image.Slices.Top, height);
            int hc = (int)Math.Max(height - image.Slices.Top - image.Slices.Bottom, 0);
            int hb = (int)Math.Min(image.Slices.Bottom, height);

            image.TopLeftViewbox = new Int32Rect(0, 0, wl, ht);
            image.TopCenterViewbox = new Int32Rect(wl, 0, wc, ht);
            image.TopRightViewbox = new Int32Rect(wl + wc, 0, wr, ht);

            image.CenterLeftViewbox = new Int32Rect(0, ht, wl, hc);
            image.CenterViewbox = new Int32Rect(wl, ht, wc, hc);
            image.CenterRightViewbox = new Int32Rect(wl + wc, ht, wr, hc);

            image.BottomLeftViewbox = new Int32Rect(0, ht + hc, wl, hb);
            image.BottomCenterViewbox = new Int32Rect(wl, ht + hc, wc, hb);
            image.BottomRightViewbox = new Int32Rect(wl + wc, ht + hc, wr, hb);
        }
    }
}
