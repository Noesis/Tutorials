using System;
using UnityEngine;

public class StandaloneInput : VirtualInput {
    public override float GetAxis (string name, bool raw) {
        return alwaysUseVirtual.Contains(name) ? virtualAxes[name].GetValue : Input.GetAxis(name);
    }

    public override bool GetButton (string name, CrossPlatformInput.ButtonAction action) {
        switch (action) {
            case CrossPlatformInput.ButtonAction.GetButton:
                return alwaysUseVirtual.Contains (name) ? virtualButtons[name].GetButton : Input.GetButton (name);
            case CrossPlatformInput.ButtonAction.GetButtonDown:
                return alwaysUseVirtual.Contains (name) ? virtualButtons[name].GetButtonDown : Input.GetButtonDown (name);
            case CrossPlatformInput.ButtonAction.GetButtonUp:
                return alwaysUseVirtual.Contains (name) ? virtualButtons[name].GetButtonUp : Input.GetButtonUp (name);
            default:
                throw new Exception("Invalid button action.");
        }
    }

    public override Vector3 MousePosition () {
        return Input.mousePosition;
    }
}
