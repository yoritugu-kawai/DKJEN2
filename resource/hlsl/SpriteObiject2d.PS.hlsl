#include"object3d.hlsli"
struct Material {
	float32_t4 color;
	float32_t4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float32_t4>gTexture:register(t0);
SamplerState gSampler:register(s0);

struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
	//float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
	float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
	float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

	output.color = gMaterial.color * textureColor;
    output.color = gTexture.Sample(gSampler, input.texcoord);
    //float32_t value  = dot(output.color.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
    //output.color.rgb = float32_t3(value, value, value);
	//output.color = gMaterial.color;
	//CG501
    //output.color = gMaterial.color * textureColor;
    //output.color = gTexture.Sample(gSampler, input.texcoord);
    //float32_t value = dot(output.color.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
    //output.color.rgb = float32_t3(value, value, value);
	//CG502
    //output.color = gTexture.Sample(gSampler, input.texcoord);
    //float32_t2 correct = input.texcoord * (1.0f - input.texcoord.yx);
    //float vignette = correct.x * correct.y * 16.0f;
    //vignette = saturate(pow(vignette, 0.8f));
    //output.color.rgb *= vignette;
    
	return output;
}
