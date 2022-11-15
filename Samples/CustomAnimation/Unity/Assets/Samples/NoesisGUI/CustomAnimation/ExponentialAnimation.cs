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
    ///     ExponentialAnimation - gets exponentially faster / slower
    /// </summary>
    public class ExponentialAnimation : DoubleAnimationBase
    {
        public enum EdgeBehaviorEnum
        {
            EaseIn,
            EaseOut,
            EaseInOut
        }

        public static readonly DependencyProperty EdgeBehaviorProperty = DependencyProperty.Register(
            "EdgeBehavior", typeof(EdgeBehaviorEnum), typeof(ExponentialAnimation),
            new PropertyMetadata(EdgeBehaviorEnum.EaseIn));

        public static readonly DependencyProperty PowerProperty = DependencyProperty.Register(
            "Power", typeof(Float), typeof(ExponentialAnimation),
            new PropertyMetadata((Float)2.0));

        public static readonly DependencyProperty FromProperty = DependencyProperty.Register(
            "From", typeof(Float?), typeof(ExponentialAnimation),
            new PropertyMetadata(null));

        public static readonly DependencyProperty ToProperty = DependencyProperty.Register(
            "To", typeof(Float?), typeof(ExponentialAnimation),
            new PropertyMetadata(null));

        /// <summary>
        ///     which side gets the effect
        /// </summary>
        public EdgeBehaviorEnum EdgeBehavior
        {
            get { return (EdgeBehaviorEnum) GetValue(EdgeBehaviorProperty); }
            set { SetValue(EdgeBehaviorProperty, value); }
        }

        /// <summary>
        ///     exponential rate of growth
        /// </summary>
        public Float Power
        {
            get { return (Float) GetValue(PowerProperty); }
            set
            {
                if (value > 0.0)
                {
                    SetValue(PowerProperty, value);
                }
                else
                {
                    throw new ArgumentException("cannot set power to less than 0.0. Value: " + value);
                }
            }
        }

        /// <summary>
        ///     Specifies the starting value of the animation.
        /// </summary>
        public Float? From
        {
            get { return (Float?) GetValue(FromProperty); }
            set { SetValue(FromProperty, value); }
        }

        /// <summary>
        ///     Specifies the ending value of the animation.
        /// </summary>
        public Float? To
        {
            get { return (Float?) GetValue(ToProperty); }
            set { SetValue(ToProperty, value); }
        }

        protected override Float GetCurrentValueCore(Float defaultOriginValue, Float defaultDestinationValue,
            AnimationClock clock)
        {
            Float returnValue;
            var start = From ?? defaultOriginValue;
            var delta = To - start ?? defaultOriginValue - start;

            switch (EdgeBehavior)
            {
                case EdgeBehaviorEnum.EaseIn:
                    returnValue = EaseIn(clock.CurrentProgress.Value, start, delta, Power);
                    break;
                case EdgeBehaviorEnum.EaseOut:
                    returnValue = EaseOut(clock.CurrentProgress.Value, start, delta, Power);
                    break;
                default:
                    returnValue = EaseInOut(clock.CurrentProgress.Value, start, delta, Power);
                    break;
            }
            return returnValue;
        }

#if !NOESIS
        protected override Freezable CreateInstanceCore() => new ExponentialAnimation();
#endif

        private static Float EaseIn(Float timeFraction, Float start, Float delta, Float power)
        {
            // math magic: simple exponential growth
            var returnValue = Math.Pow(timeFraction, power);
            returnValue *= delta;
            returnValue = returnValue + start;
            return (Float)returnValue;
        }

        private static Float EaseOut(Float timeFraction, Float start, Float delta, Float power)
        {
            // math magic: simple exponential decay
            var returnValue = Math.Pow(timeFraction, 1/power);
            returnValue *= delta;
            returnValue = returnValue + start;
            return (Float)returnValue;
        }

        private static Float EaseInOut(Float timeFraction, Float start, Float delta, Float power)
        {
            Float returnValue;

            // we cut each effect in half by multiplying the time fraction by two and halving the distance.
            if (timeFraction <= 0.5)
            {
                returnValue = EaseOut(timeFraction*2, start, delta/2, power);
            }
            else
            {
                returnValue = EaseIn((timeFraction - 0.5f)*2, start, delta/2, power);
                returnValue += (delta/2);
            }
            return (Float)returnValue;
        }
    }
}