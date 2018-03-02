using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.ComponentModel;

public class ViewModel : MonoBehaviour
{
    public Light redLight;
    public Light greenLight;

    public bool RedLightOn
    {
        get { return redLight.enabled; }
        set { redLight.enabled = value; }
    }

    public float RedLightIntensity
    {
        get { return redLight.intensity; }
        set { redLight.intensity = value; }
    }

    public bool GreenLightOn
    {
        get { return greenLight.enabled; }
        set { greenLight.enabled = value; }
    }

    public float GreenLightIntensity
    {
        get { return greenLight.intensity; }
        set { greenLight.intensity = value; }
    }

    private void Start()
    {
        NoesisView view = GetComponent<NoesisView>();
        view.Content.DataContext = this;
    }
}
