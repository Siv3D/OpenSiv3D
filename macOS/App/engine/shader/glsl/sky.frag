//	Copyright (c) 2008-2023 Ryo Suzuki.
//	Copyright (c) 2016-2023 OpenSiv3D Project.
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

# version 410

//
//	PSInput
//
layout(location = 0) in vec3 WorldPosition;
layout(location = 1) in vec2 UV;
layout(location = 2) in vec3 Normal;

//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Constant Buffer
//
layout(std140) uniform PSPerFrame
{
	vec3 g_globalAmbientColor;
	vec3 g_sunColor;
	vec3 g_sunDirection;
};

layout(std140) uniform PSPerView
{
	vec3 g_eyePosition;
};

layout(std140) uniform PSSky
{
	vec3  g_zenithColor;
	float g_fogHeightSky;

	vec3  g_horizonColor;
	float g_cloudiness;

	vec3  g_cloudUVTransform; // cos(theta), -sin(thita), sin(theta)
	float g_cloudScale;

	float g_cloudTime;
	float g_cloudPlaneHeight;
	float g_starBrightness;
	uint  g_option;

	vec3  g_cloudColor;
	float g_skyExposure;

	mat3x3 g_starsRotation;

	vec3  g_starOffset;
	float g_starSaturation;
};

//
//	Functions
//

# define OPTION_SUN_ENABLED				(1u << 0)
# define OPTION_CLOUDS_ENABLED			(1u << 1)
# define OPTION_CLOUDS_LIGHTING_ENABLED	(1u << 2)
# define PI (3.14159265f)

// o		: ray origin
// d		: ray direction
// returns distance on the ray to the object if hit, 0 otherwise
float Trace_plane(vec3 o, vec3 d, vec3 planeOrigin,vec3 planeNormal)
{
	return dot(planeNormal, (planeOrigin - o) / dot(planeNormal, d));
}

vec2 hash(vec2 p)
{
	p = vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)));
	return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
}

float noise(in vec2 p)
{
	const float K1 = 0.366025404; // (sqrt(3)-1)/2;
	const float K2 = 0.211324865; // (3-sqrt(3))/6;
	vec2 i = floor(p + (p.x + p.y) * K1);
	vec2 a = p - i + (i.x + i.y) * K2;
	vec2 o = (a.x > a.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0); //float2 of = 0.5 + 0.5*float2(sign(a.x-a.y), sign(a.y-a.x));
	vec2 b = a - o + K2;
	vec2 c = a - 1.0 + 2.0 * K2;
	vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);
	vec3 n = h * h * h * h * vec3(dot(a, hash(i + 0.0)), dot(b, hash(i + o)), dot(c, hash(i + 1.0)));
	return dot(n, vec3(70.0, 70.0, 70.0));
}

vec3 CustomAtmosphericScattering(vec3 V, vec3 sunDirection, vec3 sunColor, bool sun_enabled, bool dark_enabled)
{
	vec3 skyColor = g_zenithColor;
	bool sunDisc = sun_enabled;

	float zenith = V.y; // how much is above (0: horizon, 1: directly above)
	float sunScatter = clamp(sunDirection.y + 0.1f, 0.0f, 1.0f); // how much the sun is directly above. Even if sunis at horizon, we add a constant scattering amount so that light still scatters at horizon

	float atmosphereDensity = 0.5 + g_fogHeightSky; // constant of air density, or "fog height" as interpreted here (bigger is more obstruction of sun)
	float zenithDensity = atmosphereDensity / pow(max(0.000001f, zenith), 0.75f);
	float sunScatterDensity = atmosphereDensity / pow(max(0.000001f, sunScatter), 0.75f);

	vec3 aberration = vec3(0.39, 0.57, 1.0); // the chromatic aberration effect on the horizon-zenith fade line
	vec3 skyAbsorption = clamp(exp2(aberration * -zenithDensity) * 2.0f, 0.0f, 1.0f); // gradient on horizon
	vec3 sunAbsorption = clamp(sunColor * exp2(aberration * -sunScatterDensity) * 2.0f, 0.0f, 1.0f); // gradient of sun when it's getting below horizon

	float sunAmount = distance(V, sunDirection); // sun falloff descreasing from mid point
	float rayleigh = 1.0 + pow(1.0 - clamp(sunAmount, 0.0f, 1.0f), 2.0) * PI * 0.5;
	float mie_disk = clamp(1.0 - pow(sunAmount, 0.1), 0.0f, 1.0f);
	vec3 mie = mie_disk * mie_disk * (3.0 - 2.0 * mie_disk) * 2.0 * PI * sunAbsorption;

	vec3 totalColor = mix(g_horizonColor, g_zenithColor * zenithDensity * rayleigh, skyAbsorption);
	totalColor = mix(totalColor * skyAbsorption, totalColor, sunScatter); // when sun goes below horizon, absorb sky color
	if (sunDisc)
	{
		vec3 sun = smoothstep(0.03, 0.026, sunAmount) * sunColor * 50.0 * skyAbsorption; // sun disc
		totalColor += sun;
		totalColor += mie;
	}
	totalColor *= (sunAbsorption + length(sunAbsorption)) * 0.5f; // when sun goes below horizon, fade out whole sky
	totalColor *= 0.25; // exposure level

	if (dark_enabled)
	{
		totalColor = max(pow(clamp(dot(sunDirection, V), 0.0f, 1.0f), 64) * sunColor, 0) * skyAbsorption;
	}

	return totalColor;
}

void CalculateClouds(inout vec3 sky, vec3 V, bool cloudsLightingEnabled, bool dark_enabled)
{
	if (g_cloudiness <= 0)
	{
		return;
	}

	// Trace a cloud layer plane:
	vec3 o = g_eyePosition;
	vec3 d = V;
	vec3 planeOrigin = vec3(0, g_cloudPlaneHeight, 0);
	vec3 planeNormal = vec3(0, -1, 0);
	float t = Trace_plane(o, d, planeOrigin, planeNormal);

	if (t < 0)
	{
		return;
	}

	mat2x2 cloudUVTransform = mat2x2(g_cloudUVTransform.xy, g_cloudUVTransform.zx);
	vec2 cloudPos = o.xz + (d.xz * cloudUVTransform) * t;
	vec2 cloudUV = cloudPos * g_cloudScale;
	float cloudTime = g_cloudTime;
	mat2x2 m = mat2x2(1.6, 1.2, -1.2, 1.6);
	uint quality = 8;

	// rotate uvs like a flow effect:
	float flow = 0;
	{
		vec2 uv = cloudUV * 0.5f;
		float amount = 0.1;
		for (uint i = 0; i < quality; i++)
		{
			flow += noise(uv) * amount;
			uv = (uv * m);
			amount *= 0.4;
		}
	}

	// Main shape:
	float clouds = 0.0;
	{
		float time = cloudTime * 0.2f;
		float density = 1.1f;
		vec2 uv = cloudUV * 0.8f;
		uv -= flow - time;
		for (uint i = 0; i < quality; i++)
		{
			clouds += density * noise(uv);
			uv = (uv * m) + time;
			density *= 0.6f;
		}
	}

	// Detail shape:
	{
		float detail_shape = 0.0;
		float time = cloudTime * 0.1f;
		float density = 0.8f;
		vec2 uv = cloudUV;
		uv -= flow - time;
		for (uint i = 0; i < quality; i++)
		{
			detail_shape += abs(density * noise(uv));
			uv = (uv * m) + time;
			density *= 0.7f;
		}
		clouds *= detail_shape + clouds;
		clouds *= detail_shape;
	}

	// lerp between "choppy clouds" and "uniform clouds". Lower cloudiness will produce choppy clouds, but very high cloudiness will switch to overcast unfiform clouds:
	clouds = mix(clouds * 9.0f * g_cloudiness + 0.3f, clouds * 0.5f + 0.5f, pow(clamp(g_cloudiness, 0.0f, 1.0f), 8));
	clouds = clamp(clouds - (1 - g_cloudiness), 0.0f, 1.0f); // modulate constant cloudiness
	clouds *= pow(1 - clamp(length(abs(cloudPos * 0.00001f)), 0.0f, 1.0f), 16); //fade close to horizon

	if (dark_enabled)
	{
		sky *= pow(clamp(1 - clouds, 0.0f, 1.0f), 16.0f); // only sun and clouds. Boost clouds to have nicer sun shafts occlusion
	}
	else if (cloudsLightingEnabled)
	{
		vec3 cloudLighting = (dot(-V, g_sunDirection) * 0.5f + 0.5f) * g_sunColor * (1 - g_cloudiness);
		sky = mix(min(sky, 1.0f), g_cloudColor + cloudLighting, clouds); // sky and clouds on top
	}
	else
	{
		sky = mix(sky, g_cloudColor, clouds); // sky and clouds on top
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

vec3 GetStars(vec3 V, float starBrightness)
{
	vec3 dir = (V * g_starsRotation);
	vec3 from = g_starOffset;
	
	//volumetric rendering
	float s = 0.1f, fade = 1.0f;
	vec3 v = vec3(0.0f);

	for (uint r = 0; r < volsteps; ++r)
	{
		vec3 p = from + s * dir * 0.5f;
		p = abs(vec3(tile) - mod(p, vec3(tile * 2.0f))); // tiling fold
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
			fade*=1.-dm; // dark matter, don't render near
		}

		v += fade;
		v += vec3(s, s*s, s*s*s*s ) * a * brightness * fade; // coloring based on distance
		fade *= distfading; // distance fading
		s += stepsize;
	}

	v = mix(vec3(length(v)), v, g_starSaturation); //color adjust

	return clamp(v * V.y * 0.02f * starBrightness, 0.0f, 1.0f);
}

// Returns sky color modulated by the sun and clouds
//	V	: view direction
vec3 GetDynamicSkyColor(in vec3 V, bool sun_enabled, bool clouds_enabled, bool dark_enabled)
{
	vec3 sunDirection = g_sunDirection;
	vec3 sunColor = g_sunColor;

	vec3 sky = CustomAtmosphericScattering
	(
		V,              // normalized ray direction
		sunDirection,   // position of the sun
		sunColor,       // color of the sun, for disc
		sun_enabled,    // use sun and total
		dark_enabled    // enable dark mode for light shafts etc.
	);

	if (0.0 < g_starBrightness)
	{
		float starBrightness = g_starBrightness * (1 - g_cloudiness) * (1 - g_cloudiness);
		sky += GetStars(V, starBrightness);
	}

	sky *= g_skyExposure;

	if (clouds_enabled)
	{
		bool cloudsLightingEnabled = (g_option & OPTION_CLOUDS_LIGHTING_ENABLED) != 0;
		CalculateClouds(sky, V, cloudsLightingEnabled, dark_enabled);
	}

	return sky;
}

void main()
{
	vec3 dir = normalize(WorldPosition - g_eyePosition);

	bool sunEnabled = (g_option & OPTION_SUN_ENABLED) != 0;

	bool cloudsEnabled = (g_option & OPTION_CLOUDS_ENABLED) != 0;

	vec3 skyColor = GetDynamicSkyColor(dir, sunEnabled, cloudsEnabled, false);

	FragColor = vec4(skyColor, 1.0f);
}
