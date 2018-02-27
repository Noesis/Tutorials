# CustomControl Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/CustomControl/Screenshot.png)

This is the sample corresponding to the [CustomControl](https://www.noesisengine.com/docs/Gui.Core.CustomControlTutorial.html) tutorial.

In contrast with [UserControls](https://www.noesisengine.com/docs/Gui.Core.UserControlTutorial.html), that are created by composition of controls, a *CustomControl* **extends** an existing control. *CustomControls* can be styled and it is usually the best approach to build a control library.

Creating a *CustomControl* is quite simple but the challenge is to do it the right way. So before you start creating a control try to answer the following questions:

* What problem should my control solve?
* Who will use this control? In which context and environment?
* Can I extend or compose existing controls? Have you look at existing controls?
* Should it be possible to style or template my control?
* Is it used in a single project, or part of a reusable library?

This tutorial gives you a step by step walktrough on how to create a custom control to represent **Date and Time**.