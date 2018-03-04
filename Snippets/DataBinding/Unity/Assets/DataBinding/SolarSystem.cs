using System;
using System.Collections.Generic;
using System.Text;
using System.Collections.ObjectModel;

namespace PlanetsListBox
{
    public class SolarSystem
    {
        private ObservableCollection<SolarSystemObject> solarSystemObjects;

        public ObservableCollection<SolarSystemObject> SolarSystemObjects
        {
            get { return solarSystemObjects; }
        }
        public SolarSystem()
        {
            this.solarSystemObjects = new ObservableCollection<SolarSystemObject>();
            this.solarSystemObjects.Add(new SolarSystemObject("Sun", 0, 1380000, new Uri(@"sun", UriKind.Relative), "The yellow dwarf star in the center of our solar system."));
            this.solarSystemObjects.Add(new SolarSystemObject("Mercury", 0.38f, 4880, new Uri(@"merglobe", UriKind.Relative), "The small and rocky planet Mercury is the closest planet to the Sun."));
            this.solarSystemObjects.Add(new SolarSystemObject("Venus", 0.72f, 12103.6f, new Uri(@"venglobe", UriKind.Relative), "At first glance, if Earth had a twin, it would be Venus."));
            this.solarSystemObjects.Add(new SolarSystemObject("Earth", 1, 12756.3f, new Uri(@"earglobe", UriKind.Relative), "Earth, our home planet, is the only planet in our solar system known to harbor life."));
            this.solarSystemObjects.Add(new SolarSystemObject("Mars", 1.52f, 6794, new Uri(@"marglobe", UriKind.Relative), "The red planet Mars has inspired wild flights of imagination over the centuries."));
            this.solarSystemObjects.Add(new SolarSystemObject("Jupiter", 5.20f, 142984, new Uri(@"jupglobe", UriKind.Relative), "With its numerous moons and several rings, the Jupiter system is a \"mini-solar system.\""));
            this.solarSystemObjects.Add(new SolarSystemObject("Saturn", 9.54f, 120536, new Uri(@"2moons_2", UriKind.Relative), "Saturn is the most distant of the five planets known to ancient stargazers."));
            this.solarSystemObjects.Add(new SolarSystemObject("Uranus", 19.218f, 51118, new Uri(@"uraglobe", UriKind.Relative), "Uranus gets its blue-green color from methane gas above the deeper cloud layers."));
            this.solarSystemObjects.Add(new SolarSystemObject("Neptune", 30.06f, 49532, new Uri(@"nepglobe", UriKind.Relative), "Neptune was the first planet located through mathematical predictions."));
            this.solarSystemObjects.Add(new SolarSystemObject("Pluto", 39.5f, 2274, new Uri(@"plutoch_2", UriKind.Relative), "Long considered to be the smallest, coldest, and most distant planet from the Sun."));
        }
    }
}
