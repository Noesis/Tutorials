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
    ///     BackAnimation: goes in the opposite direction first
    /// </summary>
    public class BackAnimation : DoubleAnimationBase
    {
        public enum EdgeBehaviorEnum
        {
            EaseIn,
            EaseOut,
            EaseInOut
        }

        public static readonly DependencyProperty EdgeBehaviorProperty = DependencyProperty.Register(
            "EdgeBehavior", typeof(EdgeBehaviorEnum), typeof(BackAnimation),
            new PropertyMetadata(EdgeBehaviorEnum.EaseIn));

        public static readonly DependencyProperty AmplitudeProperty = DependencyProperty.Register(
            "Amplitude", typeof(Float), typeof(BackAnimation),
            new PropertyMetadata((Float)4.0));

        public static readonly DependencyProperty SuppressionProperty = DependencyProperty.Register(
            "Suppression", typeof(Float), typeof(BackAnimation),
            new PropertyMetadata((Float)2.0));

        public static readonly DependencyProperty FromProperty = DependencyProperty.Register(
            "From", typeof(Float?), typeof(BackAnimation),
            new PropertyMetadata(null));

        public static readonly DependencyProperty ToProperty = DependencyProperty.Register(
            "To", typeof(Float?), typeof(BackAnimation),
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
        ///     how much backwards motion is there in the effect
        /// </summary>
        public Float Amplitude
        {
            get { return (Float) GetValue(AmplitudeProperty); }
            set { SetValue(AmplitudeProperty, value); }
        }

        /// <summary>
        ///     how quickly the effect drops off vs. the entire timeline
        /// </summary>
        public Float Suppression
        {
            get { return (Float) GetValue(SuppressionProperty); }
            set { SetValue(SuppressionProperty, value); }
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
                    returnValue = EaseIn(clock.CurrentProgress.Value, start, delta, Amplitude, Suppression);
                    break;
                case EdgeBehaviorEnum.EaseOut:
                    returnValue = EaseOut(clock.CurrentProgress.Value, start, delta, Amplitude, Suppression);
                    break;
                default:
                    returnValue = EaseInOut(clock.CurrentProgress.Value, start, delta, Amplitude, Suppression);
                    break;
            }
            return returnValue;
        }

#if !NOESIS
        protected override Freezable CreateInstanceCore() => new BackAnimation();
#endif

        private static Float EaseOut(Float timeFraction, Float start, Float delta, Float amplitude,
            Float suppression)
        {
            var frequency = 0.5;

            // math magic: The sine gives us the right wave, the timeFraction * 0.5 (frequency) gives us only half 
            // of the full wave, the amplitude gives us the relative height of the peak, and the exponent makes the 
            // effect drop off more quickly by the "suppression" factor. 
            var returnValue = Math.Pow((timeFraction), suppression)
                              *amplitude*Math.Sin(2*Math.PI*timeFraction*frequency) + timeFraction;
            returnValue = (returnValue*delta);
            returnValue += start;
            return (Float)returnValue;
        }

        private static Float EaseIn(Float timeFraction, Float start, Float delta, Float amplitude,
            Float suppression)
        {
            var frequency = 0.5;

            // math magic: The sine gives us the right wave, the timeFraction * 0.5 (frequency) gives us only half 
            // of the full wave (flipped by multiplying by -1 so that we go "backwards" first), the amplitude gives 
            // us the relative height of the peak, and the exponent makes the effect start later by the "suppression" 
            // factor. 
            var returnValue = Math.Pow((1 - timeFraction), suppression)
                              *amplitude*Math.Sin(2*Math.PI*timeFraction*frequency)*-1 + timeFraction;
            returnValue = (returnValue*delta);
            returnValue += start;
            return (Float)returnValue;
        }

        private static Float EaseInOut(Float timeFraction, Float start, Float delta, Float amplitude,
            Float suppression)
        {
            Float returnValue;

            // we cut each effect in half by multiplying the time fraction by two and halving the distance.
            if (timeFraction <= 0.5)
            {
                return EaseIn(timeFraction*2, start, delta/2, amplitude, suppression);
            }
            returnValue = EaseOut((timeFraction - 0.5f)*2, start, delta/2, amplitude, suppression);
            returnValue += (delta/2);
            return (Float)returnValue;
        }
    }
}