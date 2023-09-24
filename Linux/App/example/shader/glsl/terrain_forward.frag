//	Copyright (c) 2008-2023 Ryo Suzuki.
//	Copyright (c) 2016-2023 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	Textures
//
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;

//
//	PSInput
//
layout(location = 0) in vec3 WorldPosition;
layout(location = 1) in vec2 UV;

//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Constant Buffer
//
layout(std140) uniform PSPerFrame // slot 0
{
	vec3 g_globalAmbientColor;
	vec3 g_sunColor;
	vec3 g_sunDirection;
};

layout(std140) uniform PSPerView // slot 1
{
	vec3 g_eyePosition;
};

layout(std140) uniform PSPerMaterial // slot 3
{
	vec3  g_ambientColor;
	uint  g_hasTexture;
	vec4  g_diffuseColor;
	vec3  g_specularColor;
	float g_shininess;
	vec3  g_emissionColor;
};

//
//	Functions
//
vec3 CalculateDiffuseReflection(vec3 n, vec3 l, vec3 lightColor, vec3 diffuseColor, vec3 ambientColor)
{
	vec3 directColor = lightColor * max(dot(n, l), 0.0f);
	return ((ambientColor + directColor) * diffuseColor);
}

vec3 CalculateSpecularReflection(vec3 n, vec3 h, float shininess, float nl, vec3 lightColor, vec3 specularColor)
{
	float highlight = pow(max(dot(n, h), 0.0f), shininess) * float(0.0f < nl);
	return (lightColor * specularColor * highlight);
}

vec3 FetchNormal(vec2 uv)
{
	vec2 m = texture(Texture1, uv).rg;
	return vec3(m.x, sqrt(1.0 - m.x * m.x - m.y * m.y), m.y);
}

vec4 TerrainTriplanar(vec3 worldPos, vec3 normal, float uvScale)
{
	vec4 diffuseColor = g_diffuseColor;

	if (g_hasTexture == 1)
	{
		normal.y = pow(abs(normal.y), 32.0f); // less grass on slopes

		vec3 blend = abs(normal);
		blend /= (blend.x + blend.y + blend.z);

		worldPos *= uvScale;
		vec4 c0 = texture(Texture2, worldPos.yz);
		vec4 c1 = texture(Texture0, worldPos.xz);
		vec4 c2 = texture(Texture2, worldPos.xy);

		diffuseColor *= (c0 * blend.x + c1 * blend.y + c2 * blend.z);
	}

	return diffuseColor;
}

void main()
{
	vec3 lightColor		= g_sunColor;
	vec3 lightDirection	= g_sunDirection;

	vec3 n = FetchNormal(UV);
	vec3 l = lightDirection;
	vec4 diffuseColor = TerrainTriplanar(WorldPosition, n, 0.5f);
	vec3 ambientColor = (g_ambientColor * g_globalAmbientColor);

	// Diffuse
	vec3 diffuseReflection = CalculateDiffuseReflection(n, l, lightColor, diffuseColor.rgb, ambientColor);

	// Specular
	vec3 v = normalize(g_eyePosition - WorldPosition);
	vec3 h = normalize(v + lightDirection);
	vec3 specularReflection = CalculateSpecularReflection(n, h, g_shininess, dot(n, l), lightColor, g_specularColor);

	FragColor = vec4(diffuseReflection + specularReflection + g_emissionColor, diffuseColor.a);
}
