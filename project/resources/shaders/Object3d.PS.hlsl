#include "Object3d.hlsli"

struct Material
{
    float4 color;
    int enableLighting;
};

struct DirectionalLight
{
    float4 color;
    float3 direction;
    float intensity;
};

Texture2D<float4> gtexture : register(t0);

ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

SamplerState gsampler : register(s0);

ConstantBuffer<Material> gMatterial : register(b0);

struct PixelShaderOutput
{
    float4 color : SV_Target0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    float4 textureColor = gtexture.Sample(gsampler, input.texcord);
    PixelShaderOutput output;
    if (gMatterial.enableLighting != 0)
    {
        float cos = saturate(dot(normalize(input.normal), -gDirectionalLight.direction));
        output.color = gMatterial.color * textureColor * gDirectionalLight.color;
    }
    else
    {
        output.color = gMatterial.color * textureColor;
    }
	return output;
}