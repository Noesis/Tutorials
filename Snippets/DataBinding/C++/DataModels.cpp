#include "pch.h"


using namespace Noesis;


NS_DECLARE_SYMBOL(First);
NS_DECLARE_SYMBOL(Last);
NS_DECLARE_SYMBOL(Name);
NS_DECLARE_SYMBOL(Weight);
NS_DECLARE_SYMBOL(Person);


////////////////////////////////////////////////////////////////////////////////////////////////////
class Name: public BaseComponent, public INotifyPropertyChanged
{
public:
    const NsChar* GetFirst() const
    {
        return _first.c_str();
    }

    void SetFirst(const NsChar* first)
    {
        if (_first != first)
        {
            _first = first;
            _propertyChanged(this, NSS(First));
        }
    }

    const NsChar* GetLast() const
    {
        return _last.c_str();
    }

    void SetLast(const NsChar* last)
    {
        if (_last != last)
        {
            _last = last;
            _propertyChanged(this, NSS(Last));
        }
    }

    PropertyChangedEventHandler& PropertyChanged()
    {
        return _propertyChanged;
    }

    void Serialize(SerializationData* data) const
    {
        data->Serialize("First", _first);
        data->Serialize("Last", _last);
    }

    void Unserialize(UnserializationData* data, NsUInt32 version)
    {
        data->Unserialize("First", _first);
        data->Unserialize("Last", _last);
    }

private:
    NsString _first;
    NsString _last;

    PropertyChangedEventHandler _propertyChanged;

    NS_IMPLEMENT_INLINE_REFLECTION(Name, BaseComponent)
    {
        NsMeta<TypeId>("Name");
        NsImpl<INotifyPropertyChanged>();
        NsProp("First", &Name::GetFirst, &Name::SetFirst);
        NsProp("Last", &Name::GetLast, &Name::SetLast);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Person: public BaseComponent, public INotifyPropertyChanged
{
public:
    Name* GetName() const
    {
        return _name.GetPtr();
    }

    void SetName(Name* name)
    {
        if (_name != name)
        {
            _name.Reset(name);
            _propertyChanged(this, NSS(Name));
        }
    }

    NsFloat32 GetWeight() const
    {
        return _weight;
    }

    void SetWeight(const NsFloat32 weight)
    {
        if (_weight != weight)
        {
            _weight = weight;
             _propertyChanged(this, NSS(Weight));
        }
    }

    PropertyChangedEventHandler& PropertyChanged()
    {
        return _propertyChanged;
    }

    void Serialize(SerializationData* data) const
    {
        data->Serialize("Name", _name);
        data->Serialize("Weight", _weight);
    }

    void Unserialize(UnserializationData* data, NsUInt32 version)
    {
        data->Unserialize("Name", _name);
        data->Unserialize("Weight", _weight);
    }

private:
    Ptr<Name> _name;
    NsFloat32 _weight;

    PropertyChangedEventHandler _propertyChanged;

    NS_IMPLEMENT_INLINE_REFLECTION(Person, BaseComponent)
    {
        NsMeta<TypeId>("Person");
        NsImpl<INotifyPropertyChanged>();
        NsProp("Name", &Person::GetName, &Person::SetName);
        NsProp("Weight", &Person::GetWeight, &Person::SetWeight);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class DataModel1: public BaseComponent, public INotifyPropertyChanged
{
public:
    Person* GetPerson() const
    {
        return _person.GetPtr();
    }

    void SetPerson(Person* person)
    {
        if (_person != person)
        {
            _person.Reset(person);
            _propertyChanged(this, NSS(Person));
        }
    }

    PropertyChangedEventHandler& PropertyChanged()
    {
        return _propertyChanged;
    }

    void Serialize(Noesis::Core::SerializationData* data) const
    {
        data->Serialize("Person", _person);
    }

    void Unserialize(Noesis::Core::UnserializationData* data, NsUInt32 version)
    {
        data->Unserialize("Person", _person);
    }

private:
    Ptr<Person> _person;
    PropertyChangedEventHandler _propertyChanged;

    NS_IMPLEMENT_INLINE_REFLECTION(DataModel1, BaseComponent)
    {
        NsMeta<Noesis::Core::TypeId>("DataModel1");
        NsImpl<INotifyPropertyChanged>();
        NsProp("Person", &DataModel1::GetPerson, &DataModel1::SetPerson);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class View2: public UserControl
{
public:
    const NsChar* GetText() const
    {
        return GetValue<NsString>(TextProperty).c_str();
    }

    void SetText(const NsChar* text)
    {
         SetValue<NsString>(TextProperty, text);
    }

    static const DependencyProperty* TextProperty;

private:
    NS_IMPLEMENT_INLINE_REFLECTION(View2, UserControl)
    {
        NsMeta<TypeId>("View2");

        Ptr<UIElementData> data = NsMeta<UIElementData>(TypeOf<SelfClass>());
        data->RegisterProperty<NsString>(TextProperty, "Text",
            FrameworkPropertyMetadata::Create(NsString(""), FrameworkOptions_None));
    }
};

const DependencyProperty* View2::TextProperty;

////////////////////////////////////////////////////////////////////////////////////////////////////
class Player: public BaseComponent
{
public:
    Player() {}
    Player(const NsChar* name, Color color, NsFloat32 scale, const NsChar* pos) : _name(name), 
        _scale(scale), _pos(pos), _color(*new SolidColorBrush(color)) {}

private:
    NsString _name;
    NsFloat32 _scale;
    NsString _pos;
    Ptr<Brush> _color;

    NS_IMPLEMENT_INLINE_REFLECTION(Player, BaseComponent)
    {
        NsMeta<TypeId>("Player");
        NsProp("Name", &Player::_name);
        NsProp("Scale", &Player::_scale);
        NsProp("Pos", &Player::_pos);
        NsProp("Color", &Player::_color);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class DataModel3: public BaseComponent
{
public:
    DataModel3()
    {
        _players = *new ObservableCollection<Player>;

        Ptr<Player> player0 = *new Player("Player0", Color::Red, 1.0f, "(0,0,0)");
        _players->Add(player0.GetPtr());

        Ptr<Player> player1 = *new Player("Player1", Color::Gray, 0.75f, "(0,30,0)");
        _players->Add(player1.GetPtr());

        Ptr<Player> player2 = *new Player("Player2", Color::Orange, 0.50f, "(0,-10,0)");
        _players->Add(player2.GetPtr());

        Ptr<Player> player3 = *new Player("Player3", Color::Green, 0.85f, "(0,-10,0)");
        _players->Add(player3.GetPtr());
    }

private:
    Ptr< ObservableCollection<Player> > _players;

    NS_IMPLEMENT_INLINE_REFLECTION(DataModel3, BaseComponent)
    {
        NsMeta<TypeId>("DataModel3");
        NsProp("Players", &DataModel3::_players);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Team: public BaseComponent
{
public:
    Team(const NsChar* name): _name(name) {}

private:
    NsString _name;

    NS_IMPLEMENT_INLINE_REFLECTION(Team, BaseComponent)
    {
        NsMeta<TypeId>("Team");
        NsProp("Name", &Team::_name);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Division: public BaseComponent
{
public:
    Division(const NsChar* name) : _name(name)
    {
        _teams = *new Collection();
    }

    void Add(Team* team)
    {
        _teams->Add(team);
    }

private:
    NsString _name;
    Ptr<Collection> _teams;

    NS_IMPLEMENT_INLINE_REFLECTION(Division, BaseComponent)
    {
        NsMeta<TypeId>("Division");
        NsProp("Name", &Division::_name);
        NsProp("Teams", &Division::_teams);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class League: public BaseComponent
{
public:
    League(const NsChar* name) : _name(name)
    {
        _divisions = *new Collection();
    }

    void Add(Division* division)
    {
        _divisions->Add(division);
    }

private:
    NsString _name;
    Ptr<Collection> _divisions;

    NS_IMPLEMENT_INLINE_REFLECTION(League, BaseComponent)
    {
        NsMeta<TypeId>("League");
        NsProp("Name", &League::_name);
        NsProp("Divisions", &League::_divisions);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class LeagueList: public BaseComponent
{
public:
    LeagueList()
    {
        _leagues = *new Collection();

        Ptr<League> leagueA = *new League("League A");
        _leagues->Add(leagueA.GetPtr());

        Ptr<League> leagueB = *new League("League B");
        _leagues->Add(leagueB.GetPtr());

            Ptr<Division> divisionA = *new Division("Division A");
            leagueB->Add(divisionA.GetPtr());

            Ptr<Division> divisionB = *new Division("Division B");
            leagueB->Add(divisionB.GetPtr());

            Ptr<Division> divisionC = *new Division("Division C");
            leagueB->Add(divisionC.GetPtr());

                Ptr<Team> east = *new Team("Team East");
                divisionC->Add(east.GetPtr());

                Ptr<Team> west = *new Team("Team West");
                divisionC->Add(west.GetPtr());

                Ptr<Team> north = *new Team("Team North");
                divisionC->Add(north.GetPtr());

                Ptr<Team> south = *new Team("Team South");
                divisionC->Add(south.GetPtr());

            Ptr<Division> divisionD = *new Division("Division D");
            leagueB->Add(divisionD.GetPtr());

        Ptr<League> leagueC = *new League("League C");
        _leagues->Add(leagueC.GetPtr());
    }

private:
    Ptr<Collection> _leagues;

    NS_IMPLEMENT_INLINE_REFLECTION(LeagueList, BaseComponent)
    {
        NsMeta<TypeId>("LeagueList");
        NsProp("Leagues", &LeagueList::_leagues);
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////
class SolarSystemObject: public BaseComponent
{
public:
    SolarSystemObject(const NsChar* name, NsFloat32 orbit, NsFloat32 diameter, const NsChar* image,
        const NsChar* details): _name(name), _orbit(orbit), _diameter(diameter), _details(details),
        _image(*new TextureSource(image))
    {
    }

private:
    NsString _name;
    NsFloat32 _orbit;
    NsFloat32 _diameter;
    NsString _details;
    Ptr<ImageSource> _image;

private:
    NS_IMPLEMENT_INLINE_REFLECTION(SolarSystemObject, BaseComponent)
    {
        NsMeta<TypeId>("PlanetsListBox.SolarSystemObject");
        NsProp("Name", &SolarSystemObject::_name);
        NsProp("Orbit", &SolarSystemObject::_orbit);
        NsProp("Diameter", &SolarSystemObject::_diameter);
        NsProp("Details", &SolarSystemObject::_details);
        NsProp("Image", &SolarSystemObject::_image);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class SolarSystem: public BaseComponent
{
public:
    SolarSystem()
    {
        _solarSystemObjects = *new ObservableCollection<SolarSystemObject>;

        Ptr<SolarSystemObject> sun = *new SolarSystemObject("Sun", 0, 1380000, "Images/sun.jpg",
            "The yellow dwarf star in the center of our solar system.");
        _solarSystemObjects->Add(sun.GetPtr());

        Ptr<SolarSystemObject> mercury = *new SolarSystemObject("Mercury", 0.38f, 4880, "Images/merglobe.jpg",
            "The small and rocky planet Mercury is the closest planet to the Sun.");
        _solarSystemObjects->Add(mercury.GetPtr());

        Ptr<SolarSystemObject> venus = *new SolarSystemObject("Venus", 0.72f, 12103.6f, "Images/venglobe.jpg",
            "At first glance, if Earth had a twin, it would be Venus.");
        _solarSystemObjects->Add(venus.GetPtr());

        Ptr<SolarSystemObject> earth = *new SolarSystemObject("Earth", 1, 12756.3f, "Images/earglobe.jpg",
            "Earth, our home planet, is the only planet in our solar system known to harbor life.");
        _solarSystemObjects->Add(earth.GetPtr());

        Ptr<SolarSystemObject> mars = *new SolarSystemObject("Mars", 1.52f, 6794, "Images/marglobe.jpg",
            "The red planet Mars has inspired wild flights of imagination over the centuries.");
        _solarSystemObjects->Add(mars.GetPtr());

        Ptr<SolarSystemObject> jupiter = *new SolarSystemObject("Jupiter", 5.20f, 142984, "Images/jupglobe.jpg",
            "With its numerous moons and several rings, the Jupiter system is a \"mini-solar system.\"");
        _solarSystemObjects->Add(jupiter.GetPtr());

        Ptr<SolarSystemObject> saturn = *new SolarSystemObject("Saturn", 9.54f, 120536, "Images/2moons_2.jpg",
            "Saturn is the most distant of the five planets known to ancient stargazers.");
        _solarSystemObjects->Add(saturn.GetPtr());

        Ptr<SolarSystemObject> uranus = *new SolarSystemObject("Uranus", 19.218f, 51118, "Images/uraglobe.jpg",
            "Uranus gets its blue-green color from methane gas above the deeper cloud layers.");
        _solarSystemObjects->Add(uranus.GetPtr());

        Ptr<SolarSystemObject> neptune = *new SolarSystemObject("Neptune", 30.06f, 49532, "Images/nepglobe.jpg",
            "Neptune was the first planet located through mathematical predictions.");
        _solarSystemObjects->Add(neptune.GetPtr());

        Ptr<SolarSystemObject> pluto = *new SolarSystemObject("Pluto", 39.5f, 2274, "Images/plutoch_2.jpg",
            "Long considered to be the smallest, coldest, and most distant planet from the Sun.");
        _solarSystemObjects->Add(pluto.GetPtr());
    }

private:
    Ptr< ObservableCollection<SolarSystemObject> > _solarSystemObjects;

    NS_IMPLEMENT_INLINE_REFLECTION(SolarSystem, BaseComponent)
    {
        NsMeta<TypeId>("PlanetsListBox.SolarSystem");
        NsProp("SolarSystemObjects", &SolarSystem::_solarSystemObjects);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ConvertOrbit: public BaseValueConverter
{
public:
    NsBool TryConvert(BaseComponent* value, const Type* targetType, BaseComponent* parameter, Ptr<BaseComponent>& result)
    {
        if (targetType == TypeOf<NsFloat32>() && Boxing::CanUnbox<NsFloat32>(value))
        {
            NsFloat32 orbit = Boxing::Unbox<NsFloat32>(value);
            NsFloat32 factor = (NsFloat32)atof(Boxing::Unbox<NsString>(parameter).c_str());
            result = Boxing::Box<NsFloat32>(powf(orbit / 40, 0.4f) * 770.0f * factor);
            return true;
        }

        return false;
    }

private:
    NS_IMPLEMENT_INLINE_REFLECTION(ConvertOrbit, BaseValueConverter)
    {
        NsMeta<TypeId>("PlanetsListBox.ConvertOrbit");
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" NS_DLL_EXPORT void NsRegisterReflection(ComponentFactory* factory, NsBool registerComponents)
{
    NS_REGISTER_COMPONENT(Name)
    NS_REGISTER_COMPONENT(Person)
    NS_REGISTER_COMPONENT(DataModel1)
    NS_REGISTER_COMPONENT(View2)
    NS_REGISTER_COMPONENT(Player)
    NS_REGISTER_COMPONENT(DataModel3)
    NS_REGISTER_COMPONENT(LeagueList)
    NS_REGISTER_COMPONENT(SolarSystem)
    NS_REGISTER_COMPONENT(ConvertOrbit)
}
