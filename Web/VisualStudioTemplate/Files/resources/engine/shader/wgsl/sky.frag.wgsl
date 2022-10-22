//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	https://github.com/turanszkij/WickedEngine/blob/master/WickedEngine/shaders/skyHF.hlsli
// 
//	Copyright(c) 2021 Turanszki Janos
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.

// Atmosphere based on: https://www.shadertoy.com/view/Ml2cWG
// Cloud noise based on: https://www.shadertoy.com/view/4tdSWr

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

struct PSSkyStruct
{
	zenithColor: vec3<f32>,
	fogHeightSky: f32,

	horizonColor: vec3<f32>,
	cloudiness: f32,

	cloudUVTransform: vec3<f32>, // cos(theta), -sin(thita), sin(theta)
	cloudScale: f32,

	cloudTime: f32,
	cloudPlaneHeight: f32,
	starBrightness: f32,
	option: u32,

	cloudColor: vec3<f32>,
	skyExposure: f32,

	starsRotation: mat3x3<f32>,

	starOffset: vec3<f32>,
	starSaturation: f32,
};

@group(1) @binding(3)
var<uniform> PSSky: PSSkyStruct;

//
//	Functions
//

let OPTION_SUN_ENABLED				: u32 = 1u;
let OPTION_CLOUDS_ENABLED			: u32 = 2u;
let OPTION_CLOUDS_LIGHTING_ENABLED	: u32 = 4u;
let PI: f32 = 3.14159265;

// o		: ray origin
// d		: ray direction
// returns distance on the ray to the object if hit, 0 otherwise
fn Trace_plane(o: vec3<f32>, d: vec3<f32>, planeOrigin: vec3<f32>, planeNormal: vec3<f32>) -> f32
{
	return dot(planeNormal, (planeOrigin - o) / dot(planeNormal, d));
}

fn hash(p: vec2<f32>) -> vec2<f32>
{
	let q = vec2<f32>(dot(p, vec2<f32>(127.1, 311.7)), dot(p, vec2<f32>(269.5, 183.3)));
	return -1.0 + 2.0 * fract(sin(q) * 43758.5453123);
}

fn noise(p: vec2<f32>) -> f32
{
	let K1: f32 = 0.366025404; // (sqrt(3)-1)/2;
	let K2: f32 = 0.211324865; // (3-sqrt(3))/6;
	var i: vec2<f32> = floor(p + (p.x + p.y) * K1);
	var a: vec2<f32> = p - i + (i.x + i.y) * K2;

	var o: vec2<f32>;
	if (a.x > a.y)
	{
		o = vec2<f32>(1.0, 0.0);
	}
	else
	{
		o = vec2<f32>(0.0, 1.0); 
	}
	//float2 of = 0.5 + 0.5*float2(sign(a.x-a.y), sign(a.y-a.x));

	var b: vec2<f32> = a - o + K2;
	var c: vec2<f32> = a - 1.0 + 2.0 * K2;
	var h: vec3<f32> = max(vec3<f32>(0.5) - vec3<f32>(dot(a, a), dot(b, b), dot(c, c)), vec3<f32>(0.0));
	var n: vec3<f32> = h * h * h * h * vec3<f32>(dot(a, hash(i + 0.0)), dot(b, hash(i + o)), dot(c, hash(i + 1.0)));
	return dot(n, vec3<f32>(70.0, 70.0, 70.0));
}

fn CustomAtmosphericScattering(V: vec3<f32>, sunDirection: vec3<f32>, sunColor: vec3<f32>, sun_enabled: bool, dark_enabled: bool) -> vec3<f32>
{
	var skyColor: vec3<f32> = PSSky.zenithColor;
	var sunDisc: bool = sun_enabled;

	var zenith: f32 = V.y; // how much is above (0: horizon, 1: directly above)
	var sunScatter: f32 = clamp(sunDirection.y + 0.1, 0.0, 1.0); // how much the sun is directly above. Even if sunis at horizon, we add a constant scattering amount so that light still scatters at horizon

	var atmosphereDensity: f32 = 0.5 + PSSky.fogHeightSky; // constant of air density, or "fog height" as interpreted here (bigger is more obstruction of sun)
	var zenithDensity: f32 = atmosphereDensity / pow(max(0.000001, zenith), 0.75);
	var sunScatterDensity: f32 = atmosphereDensity / pow(max(0.000001, sunScatter), 0.75);

	var aberration = vec3<f32>(0.39, 0.57, 1.0); // the chromatic aberration effect on the horizon-zenith fade line
	var skyAbsorption: vec3<f32> = clamp(exp2(aberration * -zenithDensity) * 2.0, vec3<f32>(0.0), vec3<f32>(1.0)); // gradient on horizon
	var sunAbsorption: vec3<f32> = clamp(sunColor * exp2(aberration * -sunScatterDensity) * 2.0, vec3<f32>(0.0), vec3<f32>(1.0)); // gradient of sun when it's getting below horizon

	var sunAmount: f32 = distance(V, sunDirection); // sun falloff descreasing from mid point
	var rayleigh: f32 = 1.0 + pow(1.0 - clamp(sunAmount, 0.0, 1.0), 2.0) * PI * 0.5;
	var mie_disk: f32 = clamp(1.0 - pow(sunAmount, 0.1), 0.0, 1.0);
	var mie: vec3<f32> = mie_disk * mie_disk * (3.0 - 2.0 * mie_disk) * 2.0 * PI * sunAbsorption;

	var totalColor: vec3<f32> = mix(PSSky.horizonColor, PSSky.zenithColor * zenithDensity * rayleigh, skyAbsorption);
	totalColor = mix(totalColor * skyAbsorption, totalColor, sunScatter); // when sun goes below horizon, absorb sky color
	if (sunDisc)
	{
		var sun: vec3<f32> = smoothstep(0.03, 0.026, sunAmount) * sunColor * 50.0 * skyAbsorption; // sun disc
		totalColor = totalColor + sun;
		totalColor = totalColor + mie;
	}
	totalColor = totalColor * (sunAbsorption + length(sunAbsorption)) * 0.5; // when sun goes below horizon, fade out whole sky
	totalColor = totalColor * 0.25; // exposure level

	if (dark_enabled)
	{
		totalColor = max(pow(clamp(dot(sunDirection, V), 0.0, 1.0), 64.0) * sunColor, vec3<f32>(0.0)) * skyAbsorption;
	}

	return totalColor;
}

fn CalculateClouds(sky: vec3<f32>, V: vec3<f32>, cloudsLightingEnabled: bool, dark_enabled: bool) -> vec3<f32>
{
	if (PSSky.cloudiness <= 0.0)
	{
		return sky;
	}

	// Trace a cloud layer plane:
	var o: vec3<f32> = PSPerView.eyePosition;
	var d: vec3<f32> = V;
	var planeOrigin: vec3<f32> = vec3<f32>(0.0, PSSky.cloudPlaneHeight, 0.0);
	var planeNormal: vec3<f32> = vec3<f32>(0.0, -1.0, 0.0);
	var t: f32 = Trace_plane(o, d, planeOrigin, planeNormal);

	if (t < 0.0)
	{
		return sky;
	}

	var cloudUVTransform: mat2x2<f32> = mat2x2<f32>(PSSky.cloudUVTransform.xy, PSSky.cloudUVTransform.zx);
	var cloudPos: vec2<f32> = o.xz + (d.xz * cloudUVTransform) * t;
	var cloudUV: vec2<f32> = cloudPos * PSSky.cloudScale;
	var cloudTime: f32 = PSSky.cloudTime;
	var m: mat2x2<f32> = mat2x2<f32>(1.6, 1.2, -1.2, 1.6);
	let quality: u32 = 8u;

	// rotate uvs like a flow effect:
	var flow: f32 = 0.0;
	{
		var uv: vec2<f32> = cloudUV * 0.5;
		var amount: f32 = 0.1;
		for (var i: u32 = 0u; i < quality; i = i + 1u)
		{
			flow = flow + noise(uv) * amount;
			uv = (uv * m);
			amount = amount * 0.4;
		}
	}

	// Main shape:
	var clouds: f32 = 0.0;
	{
		var time: f32 = cloudTime * 0.2;
		var density: f32 = 1.1;
		var uv: vec2<f32> = cloudUV * 0.8;
		uv = uv - (flow - time);
		for (var i: u32 = 0u; i < quality; i = i + 1u)
		{
			clouds = clouds + density * noise(uv);
			uv = (uv * m) + time;
			density = density * 0.6;
		}
	}

	// Detail shape:
	{
		var detail_shape: f32 = 0.0;
		var time: f32 = cloudTime * 0.1;
		var density: f32 = 0.8;
		var uv: vec2<f32> = cloudUV;
		uv = uv - (flow - time);
		for (var i = 0u; i < quality; i = i + 1u)
		{
			detail_shape = detail_shape + abs(density * noise(uv));
			uv = (uv * m) + time;
			density = density * 0.7;
		}
		clouds = clouds * detail_shape + clouds;
		clouds = clouds * detail_shape;
	}

	// lerp between "choppy clouds" and "uniform clouds". Lower cloudiness will produce choppy clouds, but very high cloudiness will switch to overcast unfiform clouds:
	clouds = mix(clouds * 9.0 * PSSky.cloudiness + 0.3, clouds * 0.5 + 0.5, pow(clamp(PSSky.cloudiness, 0.0, 1.0), 8.0));
	clouds = clamp(clouds - (1.0 - PSSky.cloudiness), 0.0, 1.0); // modulate constant cloudiness
	clouds = clouds * pow(1.0 - clamp(length(abs(cloudPos * 0.00001)), 0.0, 1.0), 16.0); //fade close to horizon

	if (dark_enabled)
	{
		return sky * pow(clamp(1.0 - clouds, 0.0, 1.0), 16.0); // only sun and clouds. Boost clouds to have nicer sun shafts occlusion
	}
	else if (cloudsLightingEnabled)
	{
		var cloudLighting: vec3<f32> = (dot(-V, PSPerFrame.sunDirection) * 0.5 + 0.5) * PSPerFrame.sunColor * (1.0 - PSSky.cloudiness);
		return mix(min(sky, vec3<f32>(1.0)), PSSky.cloudColor + cloudLighting, clouds); // sky and clouds on top
	}
	
	return mix(sky, PSSky.cloudColor, clouds); // sky and clouds on top
}

//	Copyright(c) Pablo Roman Andrioli
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.

// Star Nest based on: https://www.shadertoy.com/view/XlfGRj

let iterations: u32 = 22u;
let formuparam: f32 = 0.53;
let volsteps: u32 = 3u;
let stepsize: f32 = 0.1;
let tile: f32 = 0.850;
let brightness: f32 = 0.0015;
let darkmatter: f32 = 0.300;
let distfading: f32 = 0.730;

fn GetStars(V: vec3<f32>, starBrightness: f32) -> vec3<f32>
{
	var dir: vec3<f32> = (V * PSSky.starsRotation);
	var from: vec3<f32> = PSSky.starOffset;
	
	//volumetric rendering
	var s: f32 = 0.1;
	var fade: f32 = 1.0;
	var v: vec3<f32> = vec3<f32>(0.0);

	for (var r = 0u; r < volsteps; r = r + 1u)
	{
		var p: vec3<f32> = from + s * dir * 0.5;
		p = abs(vec3<f32>(tile) - (p % vec3<f32>(tile * 2.0))); // tiling fold
		var pa: f32 = 0.0;
		var a: f32 = 0.0;

		for (var i = 0u; i < iterations; i = i + 1u)
		{ 
			p = abs(p) / dot(p, p) - formuparam; // the magic formula
			a = a + abs(length(p) - pa); // absolute sum of average change
			pa = length(p);
		}

		var dm: f32 = max(0.0, darkmatter - a * a * 0.001); //dark matter
		a = a * a * a; // add contrast
		
		if (6u < r)
		{
			fade = fade * (1.0 - dm); // dark matter, don't render near
		}

		v = v + fade;
		v = v + vec3<f32>(s, s*s, s*s*s*s ) * a * brightness * fade; // coloring based on distance
		fade = fade * distfading; // distance fading
		s = s + stepsize;
	}

	v = mix(vec3<f32>(length(v)), v, PSSky.starSaturation); //color adjust

	return clamp(v * V.y * 0.02 * starBrightness, vec3<f32>(0.0), vec3<f32>(1.0));
}

// Returns sky color modulated by the sun and clouds
//	V	: view direction
fn GetDynamicSkyColor(V: vec3<f32>, sun_enabled: bool, clouds_enabled: bool, dark_enabled: bool) -> vec3<f32>
{
	var sunDirection: vec3<f32> = PSPerFrame.sunDirection;
	var sunColor: vec3<f32> = PSPerFrame.sunColor;

	var sky: vec3<f32> = CustomAtmosphericScattering
	(
		V,              // normalized ray direction
		sunDirection,   // position of the sun
		sunColor,       // color of the sun, for disc
		sun_enabled,    // use sun and total
		dark_enabled    // enable dark mode for light shafts etc.
	);

	if (0.0 < PSSky.starBrightness)
	{
		var starBrightness: f32 = PSSky.starBrightness * (1.0 - PSSky.cloudiness) * (1.0 - PSSky.cloudiness);
		sky = sky + GetStars(V, starBrightness);
	}

	sky = sky * PSSky.skyExposure;

	if (clouds_enabled)
	{
		var cloudsLightingEnabled: bool = (PSSky.option & OPTION_CLOUDS_LIGHTING_ENABLED) != 0u;
		sky = CalculateClouds(sky, V, cloudsLightingEnabled, dark_enabled);
	}

	return sky;
}

@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) WorldPosition: vec3<f32>,
	@location(1) UV: vec2<f32>,
	@location(2) Normal: vec3<f32>
) -> @location(0) vec4<f32>
{
	var dir: vec3<f32> = normalize(WorldPosition - PSPerView.eyePosition);

	var sunEnabled: bool = (PSSky.option & OPTION_SUN_ENABLED) != 0u;

	var cloudsEnabled: bool = (PSSky.option & OPTION_CLOUDS_ENABLED) != 0u;

	var skyColor: vec3<f32> = GetDynamicSkyColor(dir, sunEnabled, cloudsEnabled, false);

	return vec4<f32>(skyColor, 1.0);
}
