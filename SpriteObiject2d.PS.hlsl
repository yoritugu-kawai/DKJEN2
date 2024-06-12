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

static float32_t2 kIndex3x3[3][3] =
{
    { { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f } },
    { { -1.0f, .0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, -1.0f } },
};
static float32_t kKernal3x3[3][3] =
{
    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
};


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
	//float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
	//CG500
    //output.color = gMaterial.color * textureColor;
    //output.color = gTexture.Sample(gSampler, input.texcoord);
    //float32_t value = dot(output.color.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
    //output.color.rgb = float32_t3(value, value, value);
	//CG501
    //output.color = gTexture.Sample(gSampler, input.texcoord);
    //float32_t2 correct = input.texcoord * (1.0f - input.texcoord.yx);
    //float vignette = correct.x * correct.y * 16.0f;
    //vignette = saturate(pow(vignette, 0.8f));
    //output.color.rgb *= vignette;
    //CG502
    uint32_t widht, height;
    gTexture.GetDimensions(widht, height);
    float32_t2 uvStepSize = float32_t2(rcp(widht), rcp(height));
    
    output.color.rgb = float32_t3(0.0f, 0.0f, 0.0f);
    output.color.a = 1.0f;
    for (int32_t x = 0; x < 3; ++x)
    {
        for (int32_t y = 0; y < 3; ++y)
        {
            float32_t2 texcoord = input.texcoord + kIndex3x3[x][y] * uvStepSize;
            float32_t3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
            output.color.rgb += fetchColor * kKernal3x3[x][y];

        }

    }
	//output.color = gMaterial.color * textureColor;
    return output;
}
