//コンスタントバッファ
cbuffer GameCbuffer:register(b0)
{
    float4x4 World : packoffset(c0);
    float4x4 View : packoffset(c4);
    float4x4 Projection : packoffset(c8);
    
    //ライト情報
    
};

//コントロールバッファ
cbuffer ControllBuffer:register(b1)
{
    uint4 TexFlag : packoffset(c0);
};

struct VSPNTInput
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
};

struct PSPNTInput
{
    float4 pos : SV_Position;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
};