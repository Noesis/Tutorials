using UnityEngine;

public static class CrossPlatformInput {

	private static VirtualInput virtualInput;

    static CrossPlatformInput () {
#if UNITY_IPHONE || UNITY_ANDROID || UNITY_WP8
        virtualInput = new MobileInput ();
#elif UNITY_STANDALONE || UNITY_WEBPLAYER
        virtualInput = new StandaloneInput();
#endif
    }

	static void RegisterVirtualAxis(VirtualAxis axis) {
	    virtualInput.RegisterVirtualAxis (axis);
	}


	static void RegisterVirtualButton (VirtualButton button){
        virtualInput.RegisterVirtualButton (button);
	}


	static void UnRegisterVirtualAxis (string name){
        virtualInput.UnRegisterVirtualAxis (name);
	}


	static void UnRegisterVirtualButton (string name){
        virtualInput.UnRegisterVirtualButton (name);
	}


    // returns a reference to a named virtual axis if it exists otherwise null
	public static VirtualAxis VirtualAxisReference(string name) {
	    return virtualInput.VirtualAxisReference (name);
	}


    // returns the platform appropriate axis for the given name
	public static float GetAxis(string name) {
		return GetAxis(name, false);
	}
	
	public static float GetAxisRaw(string name) {
		return GetAxis(name, true);
	}

	// private function handles both types of axis (raw and not raw)
	private static float GetAxis(string name, bool raw)
	{
	    return virtualInput.GetAxis (name, raw);
    }



    // -- Button handling --
    public enum ButtonAction { GetButtonDown, GetButtonUp, GetButton };

	public static bool GetButton(string name)
	{
		return GetButton(name, ButtonAction.GetButton);
	}
	
	public static bool GetButtonDown(string name)
	{
		return GetButton(name, ButtonAction.GetButtonDown);
	}
	
	public static bool GetButtonUp(string name)
	{
		return GetButton(name, ButtonAction.GetButtonUp);
	}

	// private function handles all three types of button action:
	private static bool GetButton(string name, ButtonAction action)
    {
	    return virtualInput.GetButton (name, action);
	}
	
	public static Vector3 mousePosition
    {
		get {
		    return virtualInput.MousePosition ();
		}
	}

	public static void SetVirtualMousePositionX (float f)
	{
        virtualInput.SetVirtualMousePositionX (f);
	}
	public static void SetVirtualMousePositionY (float f)
	{
        virtualInput.SetVirtualMousePositionY (f);
	}
	public static void SetVirtualMousePositionZ (float f)
	{
        virtualInput.SetVirtualMousePositionZ (f);
	}


    // virtual axis and button classes - applies to mobile input
	// Can be mapped to touch joysticks, tilt, gyro, etc, depending on desired implementation.
	// Could also be implemented by other input devices - kinect, electronic sensors, etc
	public class VirtualAxis{

		public string name {get; private set;}
		float m_Value;
		public bool matchWithInputManager { get; private set; }


		public VirtualAxis(string name) : this(name, true) {}


		public VirtualAxis(string name, bool matchToInputSettings)
		{
			this.name = name;
			matchWithInputManager = matchToInputSettings;
			RegisterVirtualAxis(this);
		}

        // removes an axes from the cross platform input system
		public void Remove()
		{
			UnRegisterVirtualAxis(name);
		}

		// a controller gameobject (eg. a virtual thumbstick) should update this class
		public void Update(float value)
		{
			m_Value = value;
		}


		public float GetValue {
			get {
				return m_Value;
			}
		}


		public float GetValueRaw {
			get {
				return m_Value;
			}
		}
	}
	
    // a controller gameobject (eg. a virtual GUI button) should call the
	// 'pressed' function of this class. Other objects can then read the
	// Get/Down/Up state of this button.
	public class VirtualButton {
		
		public string name {get; private set;}
		int lastPressedFrame = -5;
	    private int releasedFrame = -5;
		bool pressed;
		public bool matchWithInputManager { get; private set; }


		public VirtualButton(string name) : this(name, true) {}
		
        
        public VirtualButton(string name, bool matchToInputSettings)
		{
			this.name = name;
			matchWithInputManager = matchToInputSettings;
			RegisterVirtualButton(this);
		}


		// A controller gameobject should call this function when the button is pressed down
		public void Pressed() { 
			if (!pressed)
				{
				pressed = true;
				lastPressedFrame = Time.frameCount;
			}
		}
		
		// A controller gameobject should call this function when the button is released
		public void Released() {
			pressed = false;
		    releasedFrame = Time.frameCount;
		}
		

		// the controller gameobject should call Remove when the button is destroyed or disabled
		public void Remove()
		{
			UnRegisterVirtualButton(name);
		}


		// these are the states of the button which can be read via the cross platform input system
		public bool GetButton {
			get {
				return pressed;
			}
		}


		public bool GetButtonDown {
			get {
			    return lastPressedFrame - Time.frameCount == 0;
			}
		}


		public bool GetButtonUp {
			get {
				return (releasedFrame == Time.frameCount - 1);
			}
		}		
	}
}
