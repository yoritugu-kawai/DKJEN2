#include"Paticle.hlsli"

struct Material
{
	float32_t4 color;
	float32_t4x4 uvTransform;
};
ConstantBuffer<Material>gMaterial :register(b0);
Texture2D<float32_t4>gTexture : register(t0);


SamplerState gSampler : register(s0);

struct PixelShaderOutput {

	float32_t4  color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;
	
	float32_t4 textureColor = gTexture.Sample(gSampler,input.texcoord);
	output.color = gMaterial.color * textureColor;
	if (textureColor.a == 0.0)
	{
		discard;
	}
	//output.color = gMatrial.color * textureColor;

	return output;
}