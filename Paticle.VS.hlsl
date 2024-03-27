#include"Paticle.hlsli"

struct TransformationMatrix {
	float32_t4x4 WVP;
	float32_t4x4 world;
	float32_t4 color;
	float32_t4x4 uvTransform;
};

StructuredBuffer<TransformationMatrix > gTransformationMatrix  : register(t0);
ConstantBuffer<TransformationMatrix> gTestTransformationMatrix : register(b1);

struct VertexShaderInput {
	float32_t4 position : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
	
};

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID) {
	VertexShaderOutput output;

	output.position = mul(input.position, gTransformationMatrix[instanceId].WVP);

	float32_t4 texposition;
	texposition.rg = input.texcoord.rg;

	texposition = mul(texposition, gTransformationMatrix[instanceId].uvTransform);

	output.position = mul(input.position, gTransformationMatrix[instanceId].WVP);
	output.texcoord = texposition.rg;
	output.normal = normalize(mul(input.normal, (float32_t3x3)gTransformationMatrix[instanceId].world));


	return output;
}
