# Custom Animations Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/CustomAnimation/Screenshot.png)

This sample shows how to create custom animations that simulate bouncing and other interesting effects.

Extending the Animation System
------------------------------

Deriving from a [[Type]AnimationBase](https://www.noesisengine.com/docs/Gui.Animation._AnimationTimeline.html) class is the simplest way to create a new animation type. Use this approach when you want to create a new animation for type that already has a corresponding [[Type]AnimationBase](https://www.noesisengine.com/docs/Gui.Animation._AnimationTimeline.html) class.

Derive from a [[Type]AnimationBase](https://www.noesisengine.com/docs/Gui.Animation._AnimationTimeline.html) class and implement the *GetCurrentValueCore* method. The *GetCurrentValueCore* method returns the current value of the animation. It takes three parameters: a suggested starting value, a suggested ending value, and an [AnimationClock](https://www.noesisengine.com/docs/Gui.Animation._AnimationClock.html), which you use to determine the progress of the animation.

Because the [[Type]AnimationBase](https://www.noesisengine.com/docs/Gui.Animation._AnimationTimeline.html) classes inherit from the [Freezable](https://www.noesisengine.com/docs/Gui.DependencySystem._Freezable.html) class, you must also override *CreateInstanceCore* core to return a new instance of your class. If the class does not use dependency properties to store its data or it requires extra initialization after creation, you might need to override additional methods.
