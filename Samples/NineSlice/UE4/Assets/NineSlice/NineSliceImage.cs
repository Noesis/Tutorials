using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

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
        public Rect TopLeftViewbox
        {
            get { return (Rect)GetValue(TopLeftViewboxProperty); }
            set { SetValue(TopLeftViewboxProperty, value); }
        }

        public static readonly DependencyProperty TopLeftViewboxProperty = DependencyProperty.Register(
            "TopLeftViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect TopCenterViewbox
        {
            get { return (Rect)GetValue(TopCenterViewboxProperty); }
            set { SetValue(TopCenterViewboxProperty, value); }
        }

        public static readonly DependencyProperty TopCenterViewboxProperty = DependencyProperty.Register(
            "TopCenterViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect TopRightViewbox
        {
            get { return (Rect)GetValue(TopRightViewboxProperty); }
            set { SetValue(TopRightViewboxProperty, value); }
        }

        public static readonly DependencyProperty TopRightViewboxProperty = DependencyProperty.Register(
            "TopRightViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect CenterLeftViewbox
        {
            get { return (Rect)GetValue(CenterLeftViewboxProperty); }
            set { SetValue(CenterLeftViewboxProperty, value); }
        }

        public static readonly DependencyProperty CenterLeftViewboxProperty = DependencyProperty.Register(
            "CenterLeftViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect CenterViewbox
        {
            get { return (Rect)GetValue(CenterViewboxProperty); }
            set { SetValue(CenterViewboxProperty, value); }
        }

        public static readonly DependencyProperty CenterViewboxProperty = DependencyProperty.Register(
            "CenterViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect CenterRightViewbox
        {
            get { return (Rect)GetValue(CenterRightViewboxProperty); }
            set { SetValue(CenterRightViewboxProperty, value); }
        }

        public static readonly DependencyProperty CenterRightViewboxProperty = DependencyProperty.Register(
            "CenterRightViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect BottomLeftViewbox
        {
            get { return (Rect)GetValue(BottomLeftViewboxProperty); }
            set { SetValue(BottomLeftViewboxProperty, value); }
        }

        public static readonly DependencyProperty BottomLeftViewboxProperty = DependencyProperty.Register(
            "BottomLeftViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect BottomCenterViewbox
        {
            get { return (Rect)GetValue(BottomCenterViewboxProperty); }
            set { SetValue(BottomCenterViewboxProperty, value); }
        }

        public static readonly DependencyProperty BottomCenterViewboxProperty = DependencyProperty.Register(
            "BottomCenterViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));

        public Rect BottomRightViewbox
        {
            get { return (Rect)GetValue(BottomRightViewboxProperty); }
            set { SetValue(BottomRightViewboxProperty, value); }
        }

        public static readonly DependencyProperty BottomRightViewboxProperty = DependencyProperty.Register(
            "BottomRightViewbox", typeof(Rect), typeof(NineSliceImage),
            new PropertyMetadata(new Rect()));
        #endregion

        private static void OnSlicesChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            NineSliceImage image = (NineSliceImage)d;

            double width = 0;
            double height = 0;

            if (image.ImageSource != null)
            {
                width = image.ImageSource.Width;
                height = image.ImageSource.Height;
            }

            double wl = Math.Min(image.Slices.Left, width);
            double wc = Math.Max(width - image.Slices.Left - image.Slices.Right, 0);
            double wr = Math.Min(image.Slices.Right, width);
            double ht = Math.Min(image.Slices.Top, height);
            double hc = Math.Max(height - image.Slices.Top - image.Slices.Bottom, 0);
            double hb = Math.Min(image.Slices.Bottom, height);

            image.TopLeftViewbox = new Rect(0, 0, wl, ht);
            image.TopCenterViewbox = new Rect(wl, 0, wc, ht);
            image.TopRightViewbox = new Rect(wl + wc, 0, wr, ht);

            image.CenterLeftViewbox = new Rect(0, ht, wl, hc);
            image.CenterViewbox = new Rect(wl, ht, wc, hc);
            image.CenterRightViewbox = new Rect(wl + wc, ht, wr, hc);

            image.BottomLeftViewbox = new Rect(0, ht + hc, wl, hb);
            image.BottomCenterViewbox = new Rect(wl, ht + hc, wc, hb);
            image.BottomRightViewbox = new Rect(wl + wc, ht + hc, wr, hb);
        }
    }
}
