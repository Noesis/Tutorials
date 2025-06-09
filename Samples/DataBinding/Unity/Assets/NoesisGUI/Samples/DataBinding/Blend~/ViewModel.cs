using System;
using System.Windows.Media.Imaging;
using System.Collections.Generic;

namespace DataBinding
{
    public class SolarSystemObject
    {
        public string Name { get; set; }
        public float Orbit { get; set; }
        public float Diameter { get; set; }
        public string Details { get; set; }
        public BitmapImage Image { get; set; }
    }

    public class SolarSystem
    {
        public List<SolarSystemObject> SolarSystemObjects { get; private set; }

        public SolarSystem()
        {
            const string BaseUri = "pack://application:,,,/DataBinding;component/Images/";

            SolarSystemObjects = new List<SolarSystemObject>
            {
                new SolarSystemObject
                {
                    Name = "Sun",
                    Orbit = 0,
                    Diameter = 1380000,
                    Details = "The yellow dwarf star in the center of our solar system.",
                    Image = new BitmapImage(new Uri(BaseUri + "sun.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Mercury",
                    Orbit = 0.38f,
                    Diameter = 4880,
                    Details = "The small and rocky planet Mercury is the closest planet to the Sun.",
                    Image = new BitmapImage(new Uri(BaseUri + "merglobe.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Venus",
                    Orbit = 0.72f,
                    Diameter = 12103.6f,
                    Details = "At first glance, if Earth had a twin, it would be Venus.",
                    Image = new BitmapImage(new Uri(BaseUri + "venglobe.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Earth",
                    Orbit = 1,
                    Diameter = 12756.3f,
                    Details = "Earth, our home planet, is the only planet in our solar system known to harbor life.",
                    Image = new BitmapImage(new Uri(BaseUri + "earglobe.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Mars",
                    Orbit = 1.52f,
                    Diameter = 6794,
                    Details = "The red planet Mars has inspired wild flights of imagination over the centuries.",
                    Image = new BitmapImage(new Uri(BaseUri + "marglobe.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Jupiter",
                    Orbit = 5.20f,
                    Diameter = 142984,
                    Details = "With its numerous moons and several rings, the Jupiter system is a \"mini-solar system\".",
                    Image = new BitmapImage(new Uri(BaseUri + "jupglobe.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Saturn",
                    Orbit = 9.54f,
                    Diameter = 120536,
                    Details = "Saturn is the most distant of the five planets known to ancient stargazers.",
                    Image = new BitmapImage(new Uri(BaseUri + "moons_2.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Uranus",
                    Orbit = 19.218f,
                    Diameter = 51118,
                    Details = "Uranus gets its blue-green color from methane gas above the deeper cloud layers.",
                    Image = new BitmapImage(new Uri(BaseUri + "uraglobe.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Neptune",
                    Orbit = 30.06f,
                    Diameter = 49532,
                    Details = "Neptune was the first planet located through mathematical predictions.",
                    Image = new BitmapImage(new Uri(BaseUri + "nepglobe.jpg"))
                },
                new SolarSystemObject
                {
                    Name = "Pluto",
                    Orbit = 39.5f,
                    Diameter = 2274,
                    Details = "Long considered to be the smallest, coldest, and most distant planet from the Sun.",
                    Image = new BitmapImage(new Uri(BaseUri + "plutoch_2.jpg"))
                }
            };
        }
    }
}
