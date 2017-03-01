using System;
using UnityEngine;

public class MobileInput : VirtualInput {

    public override float GetAxis (string name, bool raw) {
        return virtualAxes.ContainsKey(name) ? virtualAxes[name].GetValue : 0;
    }

    public override bool GetButton (string name, CrossPlatformInput.ButtonAction action) {

        bool containsName = virtualButtons.ContainsKey (name);
        if(!containsName)
            throw new Exception(" Button " + name + " does not exist");

        switch (action)
        {
            case CrossPlatformInput.ButtonAction.GetButton:
                return  virtualButtons[name].GetButton;
            case CrossPlatformInput.ButtonAction.GetButtonDown:
                return  virtualButtons[name].GetButtonDown;
            case CrossPlatformInput.ButtonAction.GetButtonUp:
                return virtualButtons[name].GetButtonUp;
            default:
                throw new Exception("Invalid button action.");
        }

    }

    public override Vector3 MousePosition () {
        return virtualMousePosition;
    }
}
