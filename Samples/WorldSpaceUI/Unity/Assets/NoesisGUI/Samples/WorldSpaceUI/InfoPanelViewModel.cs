using System;
using UnityEngine;
using Noesis;

public class InfoPanelViewModel : MonoBehaviour
{
    public string _name;
    public string Name { get => _name; }

    public float _energy;
    public float Energy { get => _energy; }

    void Start()
    {
        NoesisWorldUI ui = GetComponent<NoesisWorldUI>();
        ui.Content.DataContext = this;
    }
}
