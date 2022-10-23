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
struct GameOfLifeStruct
{
	pixelSize: vec2<f32>,
};

@group(1) @binding(1)
var<uniform> GameOfLife: GameOfLifeStruct;
// [C++]
//struct GameOfLife
//{
//	Float2 pixelSize;
//};

let offsets: array<vec2<f32>, 8> = array<vec2<f32>, 8>(
       vec2<f32>(-1.0, -1.0),
       vec2<f32>(0.0, -1.0),
       vec2<f32>(1.0, -1.0),
       vec2<f32>(-1.0, 0.0),
       vec2<f32>(1.0, 0.0),
       vec2<f32>(-1.0, 1.0),
       vec2<f32>(0.0, 1.0),
       vec2<f32>(1.0, 1.0)
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
	var c: f32 = textureSample(Texture0, Sampler0, UV).r;

	var n: f32 = 0.0;
	
	n = n + textureSample(Texture0, Sampler0, UV + offsets[0] * GameOfLife.pixelSize).r;
	n = n + textureSample(Texture0, Sampler0, UV + offsets[1] * GameOfLife.pixelSize).r;
	n = n + textureSample(Texture0, Sampler0, UV + offsets[2] * GameOfLife.pixelSize).r;
	n = n + textureSample(Texture0, Sampler0, UV + offsets[3] * GameOfLife.pixelSize).r;
	n = n + textureSample(Texture0, Sampler0, UV + offsets[4] * GameOfLife.pixelSize).r;
	n = n + textureSample(Texture0, Sampler0, UV + offsets[5] * GameOfLife.pixelSize).r;
	n = n + textureSample(Texture0, Sampler0, UV + offsets[6] * GameOfLife.pixelSize).r;
	n = n + textureSample(Texture0, Sampler0, UV + offsets[7] * GameOfLife.pixelSize).r;
	
	if((c == 0.0 && n == 3.0) || (c == 1.0 && (n == 2.0 || n == 3.0)))
	{
		return vec4<f32>(1.0, 1.0, 1.0, 1.0);
	}
	
	return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
