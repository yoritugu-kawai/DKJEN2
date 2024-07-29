#include"Object3d.hlsli"
struct Material
{
	float32_t4 color;
	int32_t enableLighting;
};
struct DirectionalLight {
	float32_t4 color;
	float32_t3 direction;
	float intensity;
};
ConstantBuffer<Material>gMaterial :register(b0);

ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

ConstantBuffer<Camera> gCamera: register(b2);

Texture2D<float32_t4>gTexture : register(t0);
//Texture2D<float32_t4> gETexture : register(t0);

SamplerState gSampler : register(s0);

struct PixelShaderOutput {

	float32_t4 color : SV_TARGET0;
};


PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;
	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

    float NdotL = dot(normalize(input.normal), normalize(gDirectionalLight.direction));

	float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
	//視点
	float32_t3 toEye = normalize(gCamera.cameraPos - input.worldPosition);
    float32_t3 reflectLight = reflect(-gDirectionalLight.direction, normalize(input.normal));
    float32_t rdotE = dot(reflectLight, toEye);
    float32_t3 halfVector = normalize(gDirectionalLight.direction + toEye);
    float NDotH = dot(normalize(input.normal), halfVector);
    float32_t specularPow = pow(saturate(NDotH), 70.0f);
    //拡散反射
    float32_t3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * 1.0f;
	//鏡面反射
    float32_t3 specular = gDirectionalLight.color.rgb * 1.0f * specularPow * float32_t3(1.0f, 1.0f, 1.0f);
	///
    float32_t3 cameraToPosition = normalize(input.worldPosition-gCamera.cameraPos);
    float32_t3 reflectedVector = reflect(cameraToPosition, normalize(input.normal));
    //float32_t3 environmetColor = gETexture.Sample(gSampler, reflectedVector);
	
    //output.color.rgb += environmetColor.rgb;
    output.color.rgb = diffuse + specular;
	output.color.a = gMaterial.color.a * textureColor.a;
	return output;
}