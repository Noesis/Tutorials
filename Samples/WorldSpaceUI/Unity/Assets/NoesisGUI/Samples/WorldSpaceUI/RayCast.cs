using System;
using UnityEngine;
using UnityEngine.XR;
using System.Collections.Generic;

namespace WorldSpaceUI
{
    public class RayCast : MonoBehaviour
    {
        public NoesisView View;
        public GameObject Object;
        public float Amplitude = 1.0f;
        public float Duration = 0.1f;

        private bool _lastHit = false;
        private InputDevice _rightController;

        void Start()
        {
            InputDeviceCharacteristics leftTrackedControllerFilter =  InputDeviceCharacteristics.Controller |
                InputDeviceCharacteristics.TrackedDevice | InputDeviceCharacteristics.Right;

            List<InputDevice> devices = new List<InputDevice>();
            InputDevices.GetDevicesWithCharacteristics(leftTrackedControllerFilter, devices);

            if (devices.Count > 0)
            {
                _rightController = devices[0];
            }
        }

        void Update()
        {
            transform.localPosition = new Vector3(0.0f, 0.0f, 2.0f);
            transform.localScale = new Vector3(0.003f, 2.0f, 0.003f);
            transform.localEulerAngles = new Vector3(90.0f, 0.0f, 0.0f);

            if (View != null && Object != null)
            {
                Noesis.Point3D pos = new Noesis.Point3D(Object.transform.position.x, Object.transform.position.y, Object.transform.position.z);
                Noesis.Vector3D dir = new Noesis.Vector3D(Object.transform.forward.x, Object.transform.forward.y, Object.transform.forward.z);

                var root = (Noesis.Visual)Noesis.VisualTreeHelper.GetRoot(View.Content);
                var result = Noesis.VisualTreeHelper.HitTest3D(root, pos, dir);

                if (result.VisualHit != null)
                {
                    float len = (result.WorldPos - pos).Length;
                    transform.localPosition = new Vector3(0.0f, 0.0f, len * 0.5f);
                    transform.localScale = new Vector3(0.003f, len * 0.5f, 0.003f);
                }

                bool hit = result.VisualHit != null;

                if (_lastHit != hit)
                {
                    if (_rightController.isValid)
                    {
                        _rightController.SendHapticImpulse(0, Amplitude, Duration); 
                    }
                }

                _lastHit = hit;
            }
        }
    }
}
