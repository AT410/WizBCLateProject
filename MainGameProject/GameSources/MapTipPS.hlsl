#include "GameShadeHeader.hlsli"

Texture2D g_BackTex : packoffset(t0);
Texture2D g_CenterTex : packoffset(t0);
Texture2D g_EffectTex : packoffset(t0);

SamplerState g_samp : packoffset(s0);


float4 main(PSPNTInput input) : SV_TARGET
{    
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}