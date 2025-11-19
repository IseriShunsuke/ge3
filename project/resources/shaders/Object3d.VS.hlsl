#include "Object3d.hlsli"

struct TransformMatrix
{
    float4x4 WVP;
    float4x4 World;
};
ConstantBuffer<TransformMatrix> gTransformMatrix : register(b0);

struct VertexShaderInput
{
    float4 position : POSITION0;
    float3 normal : NORMAL0;
    float2 texcord : TEXCOORD0;
   
};

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    output.position = mul(input.position, gTransformMatrix.WVP);
    output.texcord = input.texcord;
    output.normal = normalize(mul(input.normal, (float3x3) gTransformMatrix.World));
	return output;
}


