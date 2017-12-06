#if UNITY_5_3_OR_NEWER
#define NOESIS
using Noesis;
using UnityEngine;
#else
using System;
#endif

namespace Widget3D
{
    /// <summary>
    /// Widget3D sample view model
    /// </summary>
    public class ViewModel
    {
        public ViewModel()
        {
            SphereCommand = new DelegateCommand(this.Sphere);
            CylinderCommand = new DelegateCommand(this.Cylinder);
            BoxCommand = new DelegateCommand(this.Box);
        }

        public DelegateCommand SphereCommand { get; private set; }
        public DelegateCommand CylinderCommand { get; private set; }
        public DelegateCommand BoxCommand { get; private set; }
        
        private void Sphere(object parameter)
        {
            #if NOESIS
            Debug.Log("Sphere");
            #else
            Console.WriteLine("Sphere");
            #endif
        }

        private void Cylinder(object parameter)
        {
            #if NOESIS
            Debug.Log("Cylinder");
            #else
            Console.WriteLine("Cylinder");
            #endif
        }

        private void Box(object parameter)
        {
            #if NOESIS
            Debug.Log("Box");
            #else
            Console.WriteLine("Box");
            #endif
        }
    }
}
