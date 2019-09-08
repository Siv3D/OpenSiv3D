#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Texture0;
		
layout(location = 0) out vec4 FragColor;

// PS_0
layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
};

// PS_1
layout(std140) uniform PoissonDisk
{
	vec2  g_pixelSize;
	float g_diskRadius;
};
// [C++]
//struct PoissonDisk
//{
//	Float2 pixelSize;
//	float diskRadius;
//	float _unused = 0.0f;
//};

vec4 OutputColor(const vec4 color)
{
	return color + g_colorAdd;
}

const vec2 poisson[12] = vec2[12](
       vec2(-0.326212, -0.405805),
       vec2(-0.840144, -0.07358),
       vec2(-0.695914, 0.457137),
       vec2(-0.203345, 0.620716),
       vec2(0.96234, -0.194983),
       vec2(0.473434, -0.480026),
       vec2(0.519456, 0.767022),
       vec2(0.185461, -0.893124),
       vec2(0.507431, 0.064425),
       vec2(0.89642, 0.412458),
       vec2(-0.32194, -0.932615),
       vec2(-0.791559, -0.597705)
);
		
void main()
{
	vec4 accum = texture(Texture0, Tex);

	for (int tap = 0; tap < 12; ++tap)
	{
		vec2 texCoord = Tex + (g_pixelSize * poisson[tap] * g_diskRadius);
		accum.rgb += texture(Texture0, texCoord).rgb;
	}

	accum.rgb /= 13.0;

	FragColor = OutputColor(accum * Color);
}
