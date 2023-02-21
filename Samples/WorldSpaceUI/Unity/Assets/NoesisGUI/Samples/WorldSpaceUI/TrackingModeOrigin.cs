using UnityEngine;
using UnityEngine.XR;
using System.Collections.Generic;

namespace WorldSpaceUI
{
    public class TrackingModeOrigin : MonoBehaviour
    {
        public enum UserRequestedTrackingMode
        {
            Default,
            Device,
            Floor,
        }

        public UserRequestedTrackingMode RequestedTrackingMode = UserRequestedTrackingMode.Device;
        public float CameraYOffset = 1.36144f;

        static List<XRInputSubsystem> _inputSubsystems = new List<XRInputSubsystem>();

        void Update()
        {
            SubsystemManager.GetInstances<XRInputSubsystem>(_inputSubsystems);

            if (_inputSubsystems.Count > 0)
            {
                SetupCamera(_inputSubsystems[0]);
            }
        }

        void SetupCamera(XRInputSubsystem subsystem)
        {
            var currentMode = subsystem.GetTrackingOriginMode();
            TrackingOriginModeFlags requestedMode = currentMode;

            if (RequestedTrackingMode == UserRequestedTrackingMode.Device)
            {
                requestedMode = TrackingOriginModeFlags.Device;
            }

            if (RequestedTrackingMode == UserRequestedTrackingMode.Floor)
            {
                requestedMode = TrackingOriginModeFlags.Floor;
            }

            if (currentMode != requestedMode)
            {
                if (subsystem.TrySetTrackingOriginMode(requestedMode))
                {
                    if (requestedMode == TrackingOriginModeFlags.Device)
                    {
                        subsystem.TryRecenter();
                    }
                }
            }

            UpdateHeight(subsystem.GetTrackingOriginMode());
        }

        void UpdateHeight(TrackingOriginModeFlags mode)
        {
            if (mode == TrackingOriginModeFlags.Device)
            {
                transform.localPosition = new Vector3(transform.localPosition.x, CameraYOffset, transform.localPosition.z);
            }

            if (mode == TrackingOriginModeFlags.Floor)
            {
                transform.localPosition = new Vector3(transform.localPosition.x, 0.0f, transform.localPosition.z);
            }
        }
    }
}
