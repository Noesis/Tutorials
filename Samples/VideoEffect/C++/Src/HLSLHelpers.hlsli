struct In
{
    float4 pos: SV_POSITION;
    half4 color : COLOR;
    float2 uv : TEXCOORD;
    float4 rect : RECT;
    float4 imagePos: IMAGE_POSITION;
};

Texture2D inputTexture: register(t0);
SamplerState inputSampler: register(s0);

// Returns the current input coordinate. As the effect may be generated inside an texture atlas,
// shaders shouldn't take any dependencies on how this value is calculated. It should use it only
// to the pixel shader's input. For rest of cases GetNormalizedInputCoordinate is recommended
float2 GetInputCoordinate(in In i) { return i.uv; }

/// Returns the current normalized input coordinates in the range 0 to 1
float2 GetNormalizedInputCoordinate(in In i) { return float2((i.uv.x - i.rect.x) / (i.rect.z - i.rect.x), (i.uv.y - i.rect.y) / (i.rect.w - i.rect.y)); }

// Returns the current image position in pixels
float2 GetImagePosition(in In i) { return i.imagePos.xy; }

// Returns the current opacity
float GetOpacity(in In i) { return i.color.a; }

// Returns the color at the current input coordinates
float4 GetInput(in In i) { return inputTexture.Sample(inputSampler, i.uv); }

// Samples input at position uv
float4 SampleInput(float2 uv) { return inputTexture.Sample(inputSampler, uv); }

// Samples input at an offset in pixels from the input coordinate
float4 SampleInputAtOffset(in In i, float2 offset) { return SampleInput(clamp(i.uv + offset * i.imagePos.zw, i.rect.xy, i.rect.zw)); }

// Samples input at an absolute scene position in pixels
float4 SampleInputAtPosition(in In i, float2 pos) { return SampleInputAtOffset(i, pos - i.imagePos.xy); }
