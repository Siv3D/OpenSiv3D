//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

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

namespace s3d
{
	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position : SV_POSITION;
		float3 worldPosition : TEXCOORD0;
		float2 uv : TEXCOORD1;
		float3 normal : TEXCOORD2;
	};
}

//
//	Constant Buffer
//
cbuffer PSPerFrame : register(b0)
{
	float3 g_globalAmbientColor;
	float3 g_sunColor;
	float3 g_sunDirection;
}

cbuffer PSPerView : register(b1)
{
	float3 g_eyePosition;
}

cbuffer PSSky : register(b4)
{
	float3 g_zenithColor;
	float  g_fogHeightSky;

	float3 g_horizonColor;
	float  g_cloudiness;

	float3 g_cloudUVTransform; // cos(theta), -sin(thita), sin(theta)
	float  g_cloudScale;

	float  g_cloudTime;
	float  g_cloudPlaneHeight;
	float  g_starBrightness;
	uint   g_option;

	float3 g_cloudColor;
	float  g_skyExposure;

	row_major float3x3 g_starsRotation;

	float3 g_starOffset;
	float  g_starSaturation;
}

# define OPTION_SUN_ENABLED				(1u << 0)
# define OPTION_CLOUDS_ENABLED			(1u << 1)
# define OPTION_CLOUDS_LIGHTING_ENABLED	(1u << 2)
# define PI (3.14159265f)

// o		: ray origin
// d		: ray direction
// returns distance on the ray to the object if hit, 0 otherwise
float Trace_plane(float3 o, float3 d, float3 planeOrigin, float3 planeNormal)
{
	return dot(planeNormal, (planeOrigin - o) / dot(planeNormal, d));
}

float2 hash(float2 p)
{
	p = float2(dot(p, float2(127.1, 311.7)), dot(p, float2(269.5, 183.3)));
	return -1.0 + 2.0 * frac(sin(p) * 43758.5453123);
}

float noise(in float2 p)
{
	const float K1 = 0.366025404; // (sqrt(3)-1)/2;
	const float K2 = 0.211324865; // (3-sqrt(3))/6;
	float2 i = floor(p + (p.x + p.y) * K1);
	float2 a = p - i + (i.x + i.y) * K2;
	float2 o = (a.x > a.y) ? float2(1.0, 0.0) : float2(0.0, 1.0); //float2 of = 0.5 + 0.5*float2(sign(a.x-a.y), sign(a.y-a.x));
	float2 b = a - o + K2;
	float2 c = a - 1.0 + 2.0 * K2;
	float3 h = max(0.5 - float3(dot(a, a), dot(b, b), dot(c, c)), 0.0);
	float3 n = h * h * h * h * float3(dot(a, hash(i + 0.0)), dot(b, hash(i + o)), dot(c, hash(i + 1.0)));
	return dot(n, float3(70.0, 70.0, 70.0));
}

float3 CustomAtmosphericScattering(float3 V, float3 sunDirection, float3 sunColor, bool sun_enabled, bool dark_enabled)
{
	const float3 skyColor = g_zenithColor;
	const bool sunDisc = sun_enabled;

	const float zenith = V.y; // how much is above (0: horizon, 1: directly above)
	const float sunScatter = saturate(sunDirection.y + 0.1f); // how much the sun is directly above. Even if sunis at horizon, we add a constant scattering amount so that light still scatters at horizon

	const float atmosphereDensity = 0.5 + g_fogHeightSky; // constant of air density, or "fog height" as interpreted here (bigger is more obstruction of sun)
	const float zenithDensity = atmosphereDensity / pow(max(0.000001f, zenith), 0.75f);
	const float sunScatterDensity = atmosphereDensity / pow(max(0.000001f, sunScatter), 0.75f);

	const float3 aberration = float3(0.39, 0.57, 1.0); // the chromatic aberration effect on the horizon-zenith fade line
	const float3 skyAbsorption = saturate(exp2(aberration * -zenithDensity) * 2.0f); // gradient on horizon
	const float3 sunAbsorption = saturate(sunColor * exp2(aberration * -sunScatterDensity) * 2.0f); // gradient of sun when it's getting below horizon

	const float sunAmount = distance(V, sunDirection); // sun falloff descreasing from mid point
	const float rayleigh = 1.0 + pow(1.0 - saturate(sunAmount), 2.0) * PI * 0.5;
	const float mie_disk = saturate(1.0 - pow(sunAmount, 0.1));
	const float3 mie = mie_disk * mie_disk * (3.0 - 2.0 * mie_disk) * 2.0 * PI * sunAbsorption;

	float3 totalColor = lerp(g_horizonColor, g_zenithColor * zenithDensity * rayleigh, skyAbsorption);
	totalColor = lerp(totalColor * skyAbsorption, totalColor, sunScatter); // when sun goes below horizon, absorb sky color
	if (sunDisc)
	{
		const float3 sun = smoothstep(0.03, 0.026, sunAmount) * sunColor * 50.0 * skyAbsorption; // sun disc
		totalColor += sun;
		totalColor += mie;
	}
	totalColor *= (sunAbsorption + length(sunAbsorption)) * 0.5f; // when sun goes below horizon, fade out whole sky
	totalColor *= 0.25; // exposure level

	if (dark_enabled)
	{
		totalColor = max(pow(saturate(dot(sunDirection, V)), 64) * sunColor, 0) * skyAbsorption;
	}

	return totalColor;
}

void CalculateClouds(inout float3 sky, float3 V, bool cloudsLightingEnabled, bool dark_enabled)
{
	if (g_cloudiness <= 0)
	{
		return;
	}

	// Trace a cloud layer plane:
	const float3 o = g_eyePosition;
	const float3 d = V;
	const float3 planeOrigin = float3(0, g_cloudPlaneHeight, 0);
	const float3 planeNormal = float3(0, -1, 0);
	const float t = Trace_plane(o, d, planeOrigin, planeNormal);

	if (t < 0)
	{
		return;
	}

	const float2x2 cloudUVTransform = float2x2(g_cloudUVTransform.xy, g_cloudUVTransform.zx);
	const float2 cloudPos = o.xz + mul(cloudUVTransform, d.xz) * t;
	const float2 cloudUV = cloudPos * g_cloudScale;
	const float cloudTime = g_cloudTime;
	const float2x2 m = float2x2(1.6, 1.2, -1.2, 1.6);
	const uint quality = 8;

	// rotate uvs like a flow effect:
	float flow = 0;
	{
		float2 uv = cloudUV * 0.5f;
		float amount = 0.1;
		for (uint i = 0; i < quality; i++)
		{
			flow += noise(uv) * amount;
			uv = mul(m, uv);
			amount *= 0.4;
		}
	}

	// Main shape:
	float clouds = 0.0;
	{
		const float time = cloudTime * 0.2f;
		float density = 1.1f;
		float2 uv = cloudUV * 0.8f;
		uv -= flow - time;
		for (uint i = 0; i < quality; i++)
		{
			clouds += density * noise(uv);
			uv = mul(m, uv) + time;
			density *= 0.6f;
		}
	}

	// Detail shape:
	{
		float detail_shape = 0.0;
		const float time = cloudTime * 0.1f;
		float density = 0.8f;
		float2 uv = cloudUV;
		uv -= flow - time;
		for (uint i = 0; i < quality; i++)
		{
			detail_shape += abs(density * noise(uv));
			uv = mul(m, uv) + time;
			density *= 0.7f;
		}
		clouds *= detail_shape + clouds;
		clouds *= detail_shape;
	}

	// lerp between "choppy clouds" and "uniform clouds". Lower cloudiness will produce choppy clouds, but very high cloudiness will switch to overcast unfiform clouds:
	clouds = lerp(clouds * 9.0f * g_cloudiness + 0.3f, clouds * 0.5f + 0.5f, pow(saturate(g_cloudiness), 8));
	clouds = saturate(clouds - (1 - g_cloudiness)); // modulate constant cloudiness
	clouds *= pow(1 - saturate(length(abs(cloudPos * 0.00001f))), 16); //fade close to horizon

	if (dark_enabled)
	{
		sky *= pow(saturate(1 - clouds), 16.0f); // only sun and clouds. Boost clouds to have nicer sun shafts occlusion
	}
	else if (cloudsLightingEnabled)
	{
		const float3 cloudLighting = g_sunColor * (1 - g_cloudiness) * (dot(-V, g_sunDirection) * 0.5 + 0.5);
		sky = lerp(saturate(sky), g_cloudColor + cloudLighting, clouds); // sky and clouds on top
	}
	else
	{
		sky = lerp(sky, g_cloudColor, clouds);
	}
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

#define iterations 22
#define formuparam 0.53
#define volsteps 3
#define stepsize 0.1
#define tile   0.850
#define brightness 0.0015
#define darkmatter 0.300
#define distfading 0.730

float3 mod(float3 x, float3 y)
{
	return x - y * floor(x / y);
}

float3 GetStars(float3 V, float starBrightness)
{
	float3 dir = mul(g_starsRotation, V);
	float3 from = g_starOffset;

	//volumetric rendering
	float s = 0.1f, fade = 1.0f;
	float3 v = float3(0.0f, 0.0f, 0.0f);

	for (uint r = 0; r < volsteps; ++r)
	{
		float3 p = from + s * dir * 0.5f;
		p = abs(tile - mod(p, tile * 2.0f)); // tiling fold
		float pa = 0.0f, a = 0.0f;

		for (uint i = 0; i < iterations; ++i)
		{
			p = abs(p) / dot(p, p) - formuparam; // the magic formula
			a += abs(length(p) - pa); // absolute sum of average change
			pa = length(p);
		}

		float dm = max(0.0f, darkmatter - a * a * 0.001f); //dark matter
		a *= a * a; // add contrast

		if (6 < r)
		{
			fade *= 1. - dm; // dark matter, don't render near
		}

		v += fade;
		v += float3(s, s * s, s * s * s * s) * a * brightness * fade; // coloring based on distance
		fade *= distfading; // distance fading
		s += stepsize;
	}

	v = lerp(length(v), v, g_starSaturation); //color adjust

	return saturate(v * V.y * 0.02f * starBrightness);
}


// Returns sky color modulated by the sun and clouds
//	V	: view direction
float3 GetDynamicSkyColor(in float3 V, bool sun_enabled = true, bool clouds_enabled = true, bool dark_enabled = false)
{
	const float3 sunDirection = g_sunDirection;
	const float3 sunColor = g_sunColor;

	float3 sky = CustomAtmosphericScattering
	(
		V,              // normalized ray direction
		sunDirection,   // position of the sun
		sunColor,       // color of the sun, for disc
		sun_enabled,    // use sun and total
		dark_enabled    // enable dark mode for light shafts etc.
	);

	if (0.0 < g_starBrightness)
	{
		const float starBrightness = g_starBrightness * (1 - g_cloudiness) * (1 - g_cloudiness);
		sky += GetStars(V, starBrightness);
	}

	sky *= g_skyExposure;

	if (clouds_enabled)
	{
		const bool cloudsLightingEnabled = (g_option & OPTION_CLOUDS_LIGHTING_ENABLED);
		CalculateClouds(sky, V, cloudsLightingEnabled, dark_enabled);
	}

	return sky;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	const float3 dir = normalize(input.worldPosition - g_eyePosition);

	const bool sunEnabled = (g_option & OPTION_SUN_ENABLED);

	const bool cloudsEnabled = (g_option & OPTION_CLOUDS_ENABLED);

	const float3 skyColor = GetDynamicSkyColor(dir, sunEnabled, cloudsEnabled, false);

	return float4(skyColor, 1.0);
}
