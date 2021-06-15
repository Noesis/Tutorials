#include "HLSLHelpers.hlsli"

cbuffer Constants: register(b1)
{
    float amount;
}

float4 main(in In i): SV_TARGET
{
    float3 color;
    float offset = amount * abs(GetNormalizedInputCoordinate(i).x - 0.5);

    color.r = SampleInputAtOffset(i, float2(offset, 0.0)).r;
    color.g = GetInput(i).g;
    color.b = SampleInputAtOffset(i, float2(-offset, 0.0)).b;

    return float4(color, 1);
}