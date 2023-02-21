using System;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.XR.OpenXR.Input;

namespace WorldSpaceUI
{
    public class RayCast : MonoBehaviour
    {
        public NoesisView View;
        public GameObject Object;
        public InputActionProperty HapticAction;
        public float Amplitude = 1.0f;
        public float Duration = 0.1f;
        public float Frequency = 0.0f;

        private bool _lastHit = false;

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
                    OpenXRInput.SendHapticImpulse(HapticAction.action, Amplitude, Frequency, Duration);
                }

                _lastHit = hit;
            }
        }
    }
}
