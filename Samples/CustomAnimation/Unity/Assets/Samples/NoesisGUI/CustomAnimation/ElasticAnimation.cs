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
    ///     ElasticAnimation - like something attached to a rubber band
    /// </summary>
    public class ElasticAnimation : DoubleAnimationBase
    {
        public enum EdgeBehaviorEnum
        {
            EaseIn,
            EaseOut,
            EaseInOut
        }

        public static readonly DependencyProperty EdgeBehaviorProperty = DependencyProperty.Register(
            "EdgeBehavior", typeof(EdgeBehaviorEnum), typeof(ElasticAnimation),
            new PropertyMetadata(EdgeBehaviorEnum.EaseIn));

        public static readonly DependencyProperty SpringinessProperty = DependencyProperty.Register(
            "Springiness", typeof(Float), typeof(ElasticAnimation),
            new PropertyMetadata((Float)3.0));

        public static readonly DependencyProperty OscillationsProperty = DependencyProperty.Register(
            "Oscillations", typeof(Float), typeof(ElasticAnimation),
            new PropertyMetadata((Float)10.0));

        public static readonly DependencyProperty FromProperty = DependencyProperty.Register(
            "From", typeof(Float?), typeof(ElasticAnimation),
            new PropertyMetadata(null));

        public static readonly DependencyProperty ToProperty = DependencyProperty.Register(
            "To", typeof(Float?), typeof(ElasticAnimation),
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
        ///     how much springiness is there in the effect
        /// </summary>
        public Float Springiness
        {
            get { return (Float) GetValue(SpringinessProperty); }
            set { SetValue(SpringinessProperty, value); }
        }

        /// <summary>
        ///     number of oscillations in the effect
        /// </summary>
        public Float Oscillations
        {
            get { return (Float) GetValue(OscillationsProperty); }
            set { SetValue(OscillationsProperty, value); }
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
                    returnValue = EaseIn(clock.CurrentProgress.Value, start, delta, Springiness, Oscillations);
                    break;
                case EdgeBehaviorEnum.EaseOut:
                    returnValue = EaseOut(clock.CurrentProgress.Value, start, delta, Springiness, Oscillations);
                    break;
                default:
                    returnValue = EaseInOut(clock.CurrentProgress.Value, start, delta, Springiness, Oscillations);
                    break;
            }
            return returnValue;
        }

#if !NOESIS
        protected override Freezable CreateInstanceCore() => new ElasticAnimation();
#endif

        private static Float EaseOut(Float timeFraction, Float start, Float delta, Float springiness,
            Float oscillations)
        {
            // math magic: The cosine gives us the right wave, the timeFraction * the # of oscillations is the 
            // frequency of the wave, and the amplitude (the exponent) makes the wave get smaller at the end
            // by the "springiness" factor. This is extremely similar to the bounce equation.
            var returnValue = Math.Pow((1 - timeFraction), springiness)
                              *Math.Cos(2*Math.PI*timeFraction*oscillations);
            returnValue = delta - (returnValue*delta);
            returnValue += start;
            return (Float)returnValue;
        }

        private static Float EaseIn(Float timeFraction, Float start, Float delta, Float springiness,
            Float oscillations)
        {
            // math magic: The cosine gives us the right wave, the timeFraction * the # of oscillations is the 
            // frequency of the wave, and the amplitude (the exponent) makes the wave get smaller at the beginning
            // by the "springiness" factor. This is extremely similar to the bounce equation. 
            var returnValue = Math.Pow((timeFraction), springiness)
                              *Math.Cos(2*Math.PI*timeFraction*oscillations);
            returnValue = returnValue*delta;
            returnValue += start;
            return (Float)returnValue;
        }

        private static Float EaseInOut(Float timeFraction, Float start, Float delta, Float springiness,
            Float oscillations)
        {
            Float returnValue;

            // we cut each effect in half by multiplying the time fraction by two and halving the distance.
            if (timeFraction <= 0.5)
            {
                return EaseIn(timeFraction*2, start, delta/2, springiness, oscillations);
            }
            returnValue = EaseOut((timeFraction - 0.5f)*2, start, delta/2, springiness, oscillations);
            returnValue += (delta/2);
            return (Float)returnValue;
        }
    }
}