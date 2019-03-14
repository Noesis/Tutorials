#if NOESIS
using Noesis;
using NoesisApp;
using System;
using System.Collections.ObjectModel;
using Float = System.Single;
#else
using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Media.Imaging;
using Float = System.Double;
#endif

namespace DataBinding
{
    public class SolarSystemObject
    {
        public SolarSystemObject(string image)
        {
            Image = new BitmapImage(new Uri(image, UriKind.Relative));
        }

        public string Name { get; set; }
        public Float Orbit { get; set; }
        public Float Diameter { get; set; }
        public string Details { get; set; }
        public BitmapImage Image { get; set; }
    }

    public class SolarSystem
    {
        public ObservableCollection<SolarSystemObject> SolarSystemObjects { get; private set; }

        public SolarSystem()
        {
            SolarSystemObjects = new ObservableCollection<SolarSystemObject>
            {
                new SolarSystemObject("Images/sun.jpg")
                {
                    Name = "Sun",
                    Orbit = 0,
                    Diameter = 1380000,
                    Details = "The yellow dwarf star in the center of our solar system."
                },
                new SolarSystemObject("Images/merglobe.jpg")
                {
                    Name = "Mercury",
                    Orbit = 0.38f,
                    Diameter = 4880,
                    Details = "The small and rocky planet Mercury is the closest planet to the Sun."
                },
                new SolarSystemObject("Images/venglobe.jpg")
                {
                    Name = "Venus",
                    Orbit = 0.72f,
                    Diameter = 12103.6f,
                    Details = "At first glance, if Earth had a twin, it would be Venus."
                },
                new SolarSystemObject("Images/earglobe.jpg")
                {
                    Name = "Earth",
                    Orbit = 1,
                    Diameter = 12756.3f,
                    Details = "Earth, our home planet, is the only planet in our solar system known to harbor life."
                },
                new SolarSystemObject("Images/marglobe.jpg")
                {
                    Name = "Mars",
                    Orbit = 1.52f,
                    Diameter = 6794,
                    Details = "The red planet Mars has inspired wild flights of imagination over the centuries."
                },
                new SolarSystemObject("Images/jupglobe.jpg")
                {
                    Name = "Jupiter",
                    Orbit = 5.20f,
                    Diameter = 142984,
                    Details = "With its numerous moons and several rings, the Jupiter system is a \"mini-solar system.\""
                },
                new SolarSystemObject("Images/moons_2.jpg")
                {
                    Name = "Saturn",
                    Orbit = 9.54f,
                    Diameter = 120536,
                    Details = "Saturn is the most distant of the five planets known to ancient stargazers."
                },
                new SolarSystemObject("Images/uraglobe.jpg")
                {
                    Name = "Uranus",
                    Orbit = 19.218f,
                    Diameter = 51118,
                    Details = "Uranus gets its blue-green color from methane gas above the deeper cloud layers."
                },
                new SolarSystemObject("Images/nepglobe.jpg")
                {
                    Name = "Neptune",
                    Orbit = 30.06f,
                    Diameter = 49532,
                    Details = "Neptune was the first planet located through mathematical predictions."
                },
                new SolarSystemObject("Images/plutoch_2.jpg")
                {
                    Name = "Pluto",
                    Orbit = 39.5f,
                    Diameter = 2274,
                    Details = "Long considered to be the smallest, coldest, and most distant planet from the Sun."
                }
            };
        }
    }
}
