//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
@group(2) @binding(0) var Sampler0: sampler;
@group(2) @binding(1) var Texture0: texture_2d<f32>;

//
//	Constant Buffer
//
struct PSConstants2DStruct
{
	colorAdd: vec4<f32>,
	sdfParam: vec4<f32>,
	sdfOutlineColor: vec4<f32>,
	sdfShadowColor: vec4<f32>,
	unused: vec4<f32>,
};

@group(1) @binding(0)
var<uniform> PSConstants2D: PSConstants2DStruct;

// PS_1
struct PoissonDiskStruct
{
	pixelSize: vec2<f32>,
	diskRadius: f32,
};

@group(1) @binding(1)
var<uniform> PoissonDisk: PoissonDiskStruct;
// [C++]
//struct PoissonDisk
//{
//	Float2 pixelSize;
//	float diskRadius;
//};

let poisson: array<vec2<f32>, 12> = array<vec2<f32>, 12>(
       vec2<f32>(-0.326212, -0.405805),
       vec2<f32>(-0.840144, -0.07358),
       vec2<f32>(-0.695914, 0.457137),
       vec2<f32>(-0.203345, 0.620716),
       vec2<f32>(0.96234, -0.194983),
       vec2<f32>(0.473434, -0.480026),
       vec2<f32>(0.519456, 0.767022),
       vec2<f32>(0.185461, -0.893124),
       vec2<f32>(0.507431, 0.064425),
       vec2<f32>(0.89642, 0.412458),
       vec2<f32>(-0.32194, -0.932615),
       vec2<f32>(-0.791559, -0.597705)
);

//
//	Functions
//
@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) Color: vec4<f32>,
	@location(1) UV: vec2<f32>
) -> @location(0) vec4<f32>
{
	var offsetScale: vec2<f32> = PoissonDisk.pixelSize * PoissonDisk.diskRadius;

	var accum: vec4<f32> = textureSample(Texture0, Sampler0, UV);

	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[0] * offsetScale));
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[1] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[2] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[3] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[4] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[5] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[6] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[7] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[8] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[9] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[10] * offsetScale));	
	accum = accum + textureSample(Texture0, Sampler0, UV + (poisson[11] * offsetScale));

	accum = accum / 13.0;

	return (accum * Color) + PSConstants2D.colorAdd;
}
