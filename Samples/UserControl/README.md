# UserControl Sample

![Screenshot](https://github.com/Noesis/Noesis.github.io/blob/master/NoesisGUI/Samples/UserControl/Screenshot.png)

This is the sample corresponding to the [UserControl](https://www.noesisengine.com/docs/Gui.Core.UserControlTutorial.html) tutorial.

No modern presentation framework would be complete without the ability to create your own reusable controls. If no existing control has a programmatic interface that naturally represents your concept, go ahead and create a user control or custom control.

[UserControls](https://www.noesisengine.com/docs/Gui.Core._UserControl.html) can be seen as a composition of existing controls. They contain a logical tree defining its look and tend to have logic that directly interacts with these child elements.

In contrast [CustomControls](https://www.noesisengine.com/docs/Gui.Core.CustomControlTutorial.html) are needed when you want to create a totally new control or extend the functionality of an existing control. A custom control tends to get its look from a visual tree defined in a separate control template and generally has logic that works even if the user changes its visual tree completely.

In this tutorial we will focus on the development of a simple **user control** that implements the typical numeric spinner.