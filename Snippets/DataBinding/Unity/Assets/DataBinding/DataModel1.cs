using System.ComponentModel;

public class Name: INotifyPropertyChanged
{
    private string _first;
    public string First
    {
        get { return _first; }
        set
        {
            if (_first != value)
            {
                _first = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged(this, new PropertyChangedEventArgs("First"));
                }
            }
        }
    }

    private string _last;
    public string Last
    {
        get { return _last; }
        set
        {
            if (_last != value)
            {
                _last = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged(this, new PropertyChangedEventArgs("Last"));
                }
            }
        }
    }

    public event PropertyChangedEventHandler PropertyChanged;
}

public class Person: INotifyPropertyChanged
{
    private Name _name;
    public Name Name
    {
        get { return _name; }
        set
        {
            if (_name != value)
            {
                _name = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged(this, new PropertyChangedEventArgs("Name"));
                }
            }
        }
    }

    private float _weight;
    public float Weight
    {
        get { return _weight; }
        set
        {
            if (_weight != value)
            {
                _weight = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged(this, new PropertyChangedEventArgs("Weight"));
                }
            }
        }
    }

    public event PropertyChangedEventHandler PropertyChanged;
}

public class DataModel1
{
    private Person _person;
    public Person Person
    {
        get { return _person; }
        set
        {
            if (_person != value)
            {
                _person = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged(this, new PropertyChangedEventArgs("Person"));
                }
            }
        }
    }

    public event PropertyChangedEventHandler PropertyChanged;
}