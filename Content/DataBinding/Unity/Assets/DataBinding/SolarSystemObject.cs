using System;

namespace PlanetsListBox
{
    public class SolarSystemObject
    {
        private string _name;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        // In Astronomic Units (AU)
        private float _orbit;

        public float Orbit
        {
            get { return _orbit; }
            set { _orbit = value; }
        }

        // In Km
        private float _diameter;

        public float Diameter
        {
            get { return _diameter; }
            set { _diameter = value; }
        }

        private Uri _image;

        public Uri Image
        {
            get { return _image; }
            set { _image = value; }
        }

        private string _details;

        public string Details
        {
            get { return _details; }
            set { _details = value; }
        }

        public SolarSystemObject(string name, float orbit, float diameter, Uri image, string details)
        {
            _name = name;
            _orbit = orbit;
            _diameter = diameter;
            _image = image;
            _details = details;
        }

        public override string ToString()
        {
            return _name;
        }
    }
}
