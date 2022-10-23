//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
@group(2) @binding(0) var Sampler0: sampler;
@group(2) @binding(1) var Texture0: texture_2d<f32>;

@group(2) @binding(2) var Sampler1: sampler;
@group(2) @binding(3) var Texture1: texture_2d<f32>;

@group(2) @binding(4) var Sampler2: sampler;
@group(2) @binding(5) var Texture2: texture_2d<f32>;

//
//	Constant Buffer
//
struct PSPerFrameStruct
{
	gloablAmbientColor: vec3<f32>,
	sunColor: vec3<f32>,
	sunDirection: vec3<f32>,
};

@group(1) @binding(0)
var<uniform> PSPerFrame: PSPerFrameStruct;

struct PSPerViewStruct
{
	eyePosition: vec3<f32>,
};

@group(1) @binding(1)
var<uniform> PSPerView: PSPerViewStruct;

struct PSPerMaterialStruct
{
	amibientColor: vec3<f32>,
	hasTexture: u32,
	diffuseColor: vec4<f32>,
	specularColor: vec3<f32>,
	shininess: f32,
	emissionColor: vec3<f32>,
};

@group(1) @binding(2)
var<uniform> PSPerMaterial: PSPerMaterialStruct;

//
//	Functions
//
fn CalculateDiffuseReflection(n: vec3<f32>, l: vec3<f32>, lightColor: vec3<f32>, diffuseColor: vec3<f32>, ambientColor: vec3<f32>) -> vec3<f32>
{
	var directColor: vec3<f32> = lightColor * max(dot(n, l), 0.0);
	return ((ambientColor + directColor) * diffuseColor);
}

fn CalculateSpecularReflection(n: vec3<f32>, h: vec3<f32>, shininess: f32, nl: f32, lightColor: vec3<f32>, specularColor: vec3<f32>) -> vec3<f32>
{
	var highlight: f32 = pow(max(dot(n, h), 0.0), shininess) * f32(0.0 < nl);
	return (lightColor * specularColor * highlight);
}

fn FetchNormal(uv: vec2<f32>) -> vec3<f32>
{
	var m: vec2<f32> = textureSample(Texture1, Sampler0, uv).rg;
	return vec3<f32>(m.x, sqrt(1.0 - m.x * m.x - m.y * m.y), m.y);
}

fn TerrainTriplanar(worldPos: vec3<f32>, normal: vec3<f32>, uvScale: f32) -> vec4<f32>
{
	var diffuseColor: vec4<f32> = PSPerMaterial.diffuseColor;

	if (PSPerMaterial.hasTexture == 1u)
	{
		let powedNormal = vec3<f32>(normal.x, pow(abs(normal.y), 32.0), normal.x); // less grass on slopes

		var blend: vec3<f32> = abs(powedNormal);
		blend = blend / (blend.x + blend.y + blend.z);

		let scaledSorldPos = worldPos * uvScale;

		var c0: vec4<f32> = textureSample(Texture2, Sampler2, scaledSorldPos.yz);
		var c1: vec4<f32> = textureSample(Texture0, Sampler0, scaledSorldPos.xz);
		var c2: vec4<f32> = textureSample(Texture2, Sampler2, scaledSorldPos.xy);

		diffuseColor = diffuseColor * (c0 * blend.x + c1 * blend.y + c2 * blend.z);
	}

	return diffuseColor;
}

//
//	Functions
//
@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) WorldPosition: vec3<f32>,
	@location(1) UV: vec2<f32>
) -> @location(0) vec4<f32>
{
	var lightColor: vec3<f32>		= PSPerFrame.sunColor;
	var lightDirection: vec3<f32>	= PSPerFrame.sunDirection;

	var n: vec3<f32> = FetchNormal(UV);
	var l: vec3<f32> = lightDirection;
	var diffuseColor: vec4<f32> = TerrainTriplanar(WorldPosition, n, 0.5);
	var ambientColor: vec3<f32> = (PSPerMaterial.amibientColor * PSPerFrame.gloablAmbientColor);

	// Diffuse
	var diffuseReflection: vec3<f32> = CalculateDiffuseReflection(n, l, lightColor, diffuseColor.rgb, ambientColor);

	// Specular
	var v: vec3<f32> = normalize(PSPerView.eyePosition - WorldPosition);
	var h: vec3<f32> = normalize(v + lightDirection);
	var specularReflection: vec3<f32> = CalculateSpecularReflection(n, h, PSPerMaterial.shininess, dot(n, l), lightColor, PSPerMaterial.specularColor);

	return vec4<f32>(diffuseReflection + specularReflection + PSPerMaterial.emissionColor, diffuseColor.a);
}
