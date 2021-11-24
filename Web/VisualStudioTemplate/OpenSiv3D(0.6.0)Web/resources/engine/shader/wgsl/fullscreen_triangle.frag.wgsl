//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
[[group(0), binding(0)]] var Sampler: sampler;
[[group(0), binding(1)]] var Texture: texture_2d<f32>;

[[stage(fragment)]]
fn main(
	[[location(0)]] UV: vec2<f32>,
) -> [[location(0)]] vec4<f32> 
{
  return textureSample(Texture, Sampler, UV);
}
