using UnityEngine;

[RequireComponent(typeof(ThirdPersonCharacter))]
public class ThirdPersonUserControl : MonoBehaviour {
	
	public bool walkByDefault = false;                  // toggle for walking state
	public bool lookInCameraDirection = true;           // should the character be looking in the same direction that the camera is facing
	
    private Transform cam;                              // A reference to the main camera in the scenes transform
	private Vector3 lookPos;                            // The position that the character should be looking towards
    private ThirdPersonCharacter character;             // A reference to the ThirdPersonCharacter on the object

	// Use this for initialization
	void Start ()
	{
        // get the transform of the main camera
		cam = Camera.main.transform;

        // get the third person character ( this should never be null due to require component )
		character = GetComponent<ThirdPersonCharacter>();
	}

	// Fixed update is called in sync with physics
	void FixedUpdate ()
	{
		// read inputs
		bool crouch = Input.GetKey(KeyCode.C);
		bool jump = CrossPlatformInput.GetButton("Jump");
		float h = CrossPlatformInput.GetAxis("Horizontal");
		float v = CrossPlatformInput.GetAxis("Vertical");

		// calculate move direction to pass to character
		Vector3 camForward = Vector3.Scale (cam.forward, new Vector3(1,0,1)).normalized;
		Vector3 move = v * camForward + h * cam.right;	

		#if !(UNITY_IPHONE || UNITY_ANDROID || UNITY_WP8)
		// On standalone builds, walk/run speed is modified by a key press.
		bool walkToggle = Input.GetKey(KeyCode.LeftShift);
		// We select appropriate speed based on whether we're walking by default, and whether the walk/run toggle button is pressed:
		float walkMultiplier = (walkByDefault ? walkToggle ? 1 : 0.5f : walkToggle ? 0.5f : 1);
		move *= walkMultiplier;
		#endif

		// On mobile, it's controlled in analogue fashion by the v input value, and therefore needs no special handling.


		// calculate the head look target position
	    lookPos = lookInCameraDirection && cam != null
	                  ? transform.position + cam.forward * 100
	                  : transform.position + transform.forward * 100;

	    // pass all parameters to the character control script
		character.Move( move, crouch, jump, lookPos );
	}


}
