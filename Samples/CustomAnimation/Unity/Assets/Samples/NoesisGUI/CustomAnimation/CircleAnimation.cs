// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using System;
using Float = System.Single;
#else
using System;
using System.Windows;
using System.Windows.Media.Animation;
using Float = System.Double;
#endif

namespace CustomAnimation
{
    /// <summary>
    ///     CircleAnimation: calculates polar coordinates as a function of time.
    ///     Use two of these (XDirection and YDirection) to move an element in an elliptical manner
    /// </summary>
    public class CircleAnimation : DoubleAnimationBase
    {
        public enum DirectionEnum
        {
            XDirection,
            YDirection
        }

        public static readonly DependencyProperty DirectionProperty = DependencyProperty.Register(
            "Direction", typeof(DirectionEnum), typeof(CircleAnimation),
            new PropertyMetadata(DirectionEnum.XDirection));

        public static readonly DependencyProperty RadiusProperty = DependencyProperty.Register(
            "Radius", typeof(Float), typeof(CircleAnimation),
            new PropertyMetadata((Float)10));

        /// <summary>
        ///     distance from origin to polar coordinate
        /// </summary>
        public Float Radius
        {
            get { return (Float) GetValue(RadiusProperty); }
            set { SetValue(RadiusProperty, value); }
        }

        /// <summary>
        ///     are we measuring in the X or Y direction?
        /// </summary>
        public DirectionEnum Direction
        {
            get { return (DirectionEnum) GetValue(DirectionProperty); }
            set { SetValue(DirectionProperty, value); }
        }

        protected override Float GetCurrentValueCore(Float defaultOriginValue, Float defaultDestinationValue,
            AnimationClock clock)
        {
            var time = clock.CurrentProgress.Value;

            // math magic: calculate new coordinates using polar coordinate equations. This requires two 
            // animations to be wired up in order to move in a circle, since we don't make any assumptions
            // about what we're animating (e.g. a TranslateTransform).
            var returnValue = Direction == DirectionEnum.XDirection
                ? 1 - Math.Cos(2*Math.PI*time)
                : -Math.Sin(2*Math.PI*time);

            // Need to add the defaultOriginValue so that composition works.
            return (Float)returnValue*Radius + defaultOriginValue;
        }

#if !NOESIS
        protected override Freezable CreateInstanceCore() => new CircleAnimation();
#endif
    }
}