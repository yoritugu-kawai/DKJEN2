#include "AnimationObject3D.hlsli"
struct Material
{
    float32_t4 color;
    int32_t enableLighting;
};
struct DirectionalLight
{
    float32_t4 color;
    float32_t3 direction;
    float intensity;
};
ConstantBuffer<Material> gMaterial : register(b0);

ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

ConstantBuffer<Camera> gCamera : register(b2);

Texture2D<float32_t4> gTexture : register(t0);
TextureCube<float32_t4> gEnviromentTexture : register(t2);

SamplerState gSampler : register(s0);

struct PixelShaderOutput
{

    float32_t4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

    float NdotL = dot(normalize(input.normal), normalize(gDirectionalLight.direction));

    float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
	//視点
    float3 toEye = normalize(gCamera.cameraPos - input.worldPosition);
    float3 reflectLight = reflect(-gDirectionalLight.direction, normalize(input.normal));
    float rdotE = dot(reflectLight, toEye);
    float3 halfVector = normalize(gDirectionalLight.direction + toEye);
    float NDotH = dot(normalize(input.normal), halfVector);
    float specularPow = pow(saturate(NDotH), 70.0f);
    //拡散反射
    float3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * 1.0f;
	//鏡面反射
    float3 specular = gDirectionalLight.color.rgb * 1.0f * specularPow * float3(1.0f, 1.0f, 1.0f);
    float3 cameraToPosition = normalize(input.worldPosition - gCamera.cameraPos);
    float3 reflectedVector = reflect(cameraToPosition, normalize(input.normal));
    float4 environmetColor = gEnviromentTexture.Sample(gSampler, reflectedVector);
	
    output.color.rgb = environmetColor.rgb;
    //output.color.rgb = diffuse + specular;
	
    output.color.a = gMaterial.color.a * textureColor.a;
    return output;
}