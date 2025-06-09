using UnityEngine;

public class WASDController : MonoBehaviour
{
    public float keyboardMoveSpeed = 5f;
    public float mouseTurnSpeed = 0.4f;

    float _rotX = 0.0f;
    bool _rotating = false;
  
    void Update()
    {
      #if ENABLE_LEGACY_INPUT_MANAGER
        if (Input.GetMouseButtonDown(1))
        {
            _rotating = true;
        }
        else if (Input.GetMouseButtonUp(1))
        {
            _rotating = false;
        }
      #else
        _rotating = UnityEngine.InputSystem.Mouse.current.rightButton.isPressed;
      #endif

        if (_rotating)
        {
          #if ENABLE_LEGACY_INPUT_MANAGER
            float mouseX = Input.mousePositionDelta.x;
            float mouseY = Input.mousePositionDelta.y;
          #else
            float mouseX = UnityEngine.InputSystem.Mouse.current.delta.x.ReadValue();
            float mouseY = UnityEngine.InputSystem.Mouse.current.delta.y.ReadValue();
          #endif

            float y = mouseX * mouseTurnSpeed;
            _rotX += mouseY * mouseTurnSpeed;

            transform.eulerAngles = new Vector3(-_rotX, transform.eulerAngles.y + y, 0);
        }

        Vector3 dir = new Vector3(0, 0, 0);

      #if ENABLE_LEGACY_INPUT_MANAGER
        if (Input.GetKey("a")) dir.x = -1.0f;
        if (Input.GetKey("d")) dir.x = 1.0f;
        if (Input.GetKey("w")) dir.z = 1.0f;
        if (Input.GetKey("s")) dir.z = -1.0f;
      #else
        if (UnityEngine.InputSystem.Keyboard.current.aKey.isPressed) dir.x = -1.0f;
        if (UnityEngine.InputSystem.Keyboard.current.dKey.isPressed) dir.x = 1.0f;
        if (UnityEngine.InputSystem.Keyboard.current.wKey.isPressed) dir.z = 1.0f;
        if (UnityEngine.InputSystem.Keyboard.current.sKey.isPressed) dir.z = -1.0f;
      #endif

        transform.Translate(dir * keyboardMoveSpeed * Time.deltaTime);
    }
}