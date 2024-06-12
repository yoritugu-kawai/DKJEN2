#include"object3d.hlsli"
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    int type;
    float4 color;
};
ConstantBuffer<Material> gMaterial : register(b1);

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


   static const float32_t PI = 3.14159265f;
float gauss(float x, float y,float sigma){
    float exponent = -(x * x + y * y) * rcp(2.0f * sigma * sigma);
    float denominator = 2.0f * PI * sigma * sigma;
    return exp(exponent) * rcp(denominator);
}


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    if (gMaterial.type == 0) // None
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
    }
    else if (gMaterial.type == 1) // GrayScale
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
        float value = dot(output.color.rgb, float3(0.2125f, 0.7154f, 0.0721f));
        output.color.rgb = float3(value, value, value);
    }
    else if (gMaterial.type == 2) // Sepia
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
        float3 originalColor = output.color.rgb;

        float3 sepiaColor;
        sepiaColor.r = dot(originalColor, float3(0.393, 0.769, 0.189));
        sepiaColor.g = dot(originalColor, float3(0.349, 0.686, 0.168));
        sepiaColor.b = dot(originalColor, float3(0.272, 0.534, 0.131));

        output.color.rgb = sepiaColor;
    }
    else if (gMaterial.type == 3) // Vignetting
    {
        output.color = gTexture.Sample(gSampler, input.texcoord);
        
        // 周囲を0に、中心になるほど明るくなるように計算で調整
        float2 corrext = input.texcoord * (1.0f - input.texcoord.yx);
        // correctだけで計算すると中心の最大値が0.0625で暗すぎるのでScaleで調整。この例では16倍にして1にしてる
        float vignette = corrext.x * corrext.y * 16.0f;
        // とりあえず0.8乗でそれっぽくする
        vignette = saturate(pow(vignette, 0.8f));
        // 係数として乗算
        output.color.rgb *= vignette;
    }
    else if (gMaterial.type == 4) // Smoothing
    {
        //// 1. uvStepSizeの算出
        //uint width, height;
        //gTexture.GetDimensions(width, height);
        //float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
        //output.color.rgb = float3(0.0f, 0.0f, 0.0f);
        //output.color.a = 1.0f;
        
        //// 2. 3x3ループ
        //for (uint x = 0; x < 3; ++x)
        //{
        //    for (uint y = 0; y < 3; ++y)
        //    {
        //        // 3. 現在のtexcoordを算出
        //        float2 texcoord = input.texcoord + kINdex3x3[x][y] * uvStepSize;
                
        //        // 4. 色に 1/9 掛けて足す
        //        float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
        //        output.color.rgb += fetchColor * kKernel3x3[x][y];
        //    }
        //}
        
        // 1. uvStepSizeの算出
        uint width, height;
        gTexture.GetDimensions(width, height);
        float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
        output.color.rgb = float3(0.0f, 0.0f, 0.0f);
        output.color.a = 1.0f;
        
        // 2. 5x5ループ
        for (uint x = 0; x < 5; ++x)
        {
            for (uint y = 0; y < 5; ++y)
            {
                // 3. 現在のtexcoordを算出
                float2 texcoord = input.texcoord + kINdex5x5[x][y] * uvStepSize;
                
                // 4. 色に 1/25 掛けて足す
                float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
                output.color.rgb += fetchColor * kKernel5x5[x][y];
            }
        }
    }
    else if (gMaterial.type == 5) // GaussianFilter
    {
        // kenrnelを求める。weightは後で使う
        float weight = 0.0f;
        float kernel3x3[3][3];
        
        // uvStepSizeの算出
        uint width, height;
        gTexture.GetDimensions(width, height);
        float2 uvStepSize = float2(rcp((float) width), rcp((float) height));
        
        output.color.rgb = float3(0.0f, 0.0f, 0.0f);
        output.color.a = 1.0f;
        
        // gauss関数でkernelを求める
        for (uint i = 0; i < 3; ++i)
        {
            for (uint j = 0; j < 3; ++j)
            {
                kernel3x3[i][j] = gauss(kINdex3x3[i][j].x, kINdex3x3[i][j].y, 2.0f);
                weight += kernel3x3[i][j];
            }
        }
        
        // 求めたkernelを使い、BoxFilterと同じく畳み込みを行う。kKernel3x3と定数にしていたところがkernel3x3に代わるだけ
        for (uint k = 0; k < 3; ++k)
        {
            for (uint l = 0; l < 3; ++l)
            {
                // 3. 現在のtexcoordを算出
                float2 texcoord = input.texcoord + kINdex3x3[k][l] * uvStepSize;
              
                // 4. 色に kernel 掛けて足す
                float3 fetchColor = gTexture.Sample(gSampler, texcoord).rgb;
                output.color.rgb += fetchColor * kernel3x3[k][l];
            }
        }
        
        // 畳み込み後の値を正規化する。本来gauss関数は全体を合計すると(積分)1になるように設計されている
        // しかし、無限の範囲果たせないので、kernek値の合計である
        //　weightは1に満たない。なので合計が1になるように逆数をかけて全体を底上げして調整する
        output.color.rgb *= rcp(weight);
    }
    
    return output;
}