#include"object3d.hlsli"
struct Material
{
    float32_t4 color;
    float32_t4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

static float32_t2 kIndex3x3[3][3] =
{
    { { -1.0f, -1.0f }, { 0.0f, -1.0f }, { 1.0f, -1.0f } },
    { { -1.0f, .0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -1.0f, 1.0f }, { 0.0f, 1.0f }, { 1.0f, -1.0f } },
};
//static const float32_t3 kKernal3x3[3][3] =
//{
//    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
//    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
//    { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
//};

static const float32_t PI = 3.14159265f;
float gauss(float x, float y, float sigma)
{
    float exponent = -(x * x + y * y) * rcp(2.0f * sigma * sigma);
    float denominator = 2.0f * PI * sigma * sigma;
    
    return exp(exponent) * rcp(denominator);
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
	//float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    float32_t wight = 0.0f;
    float32_t kerne3x3[3][3];
    for (int32_t x = 0; x < 3; ++x)
    {
        for (int32_t y = 0; y < 3; ++y)
        {
            kerne3x3[x][y] = gauss(kIndex3x3[x][y].x, kIndex3x3[x][y].y, 2.0f);
            wight += kerne3x3[x][y];

        }

    }
    uint32_t widht, height;
    gTexture.GetDimensions(widht, height);
    float32_t2 uvStepSize = float32_t2(rcp(widht), rcp(height));
    
    output.color.rgb = float32_t3(0.0f, 0.0f, 0.0f);
    output.color.a = 1.0f;
    for (int32_t lx = 0; lx < 3; ++lx)
    {
        for (int32_t ly = 0; ly < 3; ++ly)
        {
            float32_t2 texcoord = input.texcoord + kIndex3x3[lx][ly] * uvStepSize;
            float32_t3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
            output.color.rgb += fetchColor * kerne3x3[lx][ly];

        }

    }
    //output.color = textureColor;
    output.color.rgb *= rcp(wight);
	//output.color = gMaterial.color;
    return output;
}
