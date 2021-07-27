#include "GameShadeHeader.hlsli"

PSPNTInput main(VSPNTInput input)
{
    PSPNTInput result;
    float4 pos = float4(input.pos.xyz,1.0f);
    pos = mul(pos, World);
    pos = mul(pos, View);
    pos = mul(pos, Projection);
    
    result.pos = pos;
    
    //Normal
    float4 normal = mul(input.normal, (float3x3) World);
    result.normal = normalize(normal);
    
    result.tex = input.tex;
    return result;
}