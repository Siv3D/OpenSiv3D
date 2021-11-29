//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Sky.hpp>
# include <Siv3D/MeshData.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/FastMath.hpp>
# include <Siv3D/ScopedCustomShader3D.hpp>
# include <Siv3D/ScopedRenderStates3D.hpp>

namespace s3d
{
	Sky::Sky(const double sphereRadius)
		: m_skySphere{ MeshData::Sphere(sphereRadius, 3).flipTriangles() }
		, m_pixelShader{ HLSL{ Resource(U"engine/shader/d3d11/sky.ps") }
			| GLSL{ Resource(U"engine/shader/glsl/sky.frag"), {{U"PSPerFrame",0}, {U"PSPerView",1}, {U"PSSky",4}} }
			| ESSL{ Resource(U"engine/shader/essl/sky.frag"), {{U"PSPerFrame",0}, {U"PSPerView",1}, {U"PSSky",4}} }
			| WGSL{ Resource(U"engine/shader/wgsl/sky.frag.wgsl"), {{U"PSPerFrame",0}, {U"PSPerView",1}, {U"PSPerMaterial",2}, {U"PSSky",3}} } } {}

	void Sky::draw(const double exposure) const
	{
		Graphics3D::SetConstantBuffer(ShaderStage::Pixel, 4, m_constants);

		m_constants = toConstants(exposure);

		const ScopedCustomShader3D shader{ m_pixelShader };

		const ScopedRenderStates3D rs{ DepthStencilState::DepthTest, BlendState::Opaque };

		m_skySphere.draw(Graphics3D::GetEyePosition());
	}

	Sky::PSConstantsSky Sky::toConstants(double exposure) const
	{
		Float3 starFrom = Vec3(1.0f, 0.5f, 0.5f);
		{
			const Float2 xz = Mat3x2::Rotate(starOffset.x).transformPoint(starFrom.xz());
			starFrom.x = xz.x;
			starFrom.z = xz.y;

			const Float2 xy = Mat3x2::Rotate(starOffset.y).transformPoint(starFrom.xy());
			starFrom.x = xy.x;
			starFrom.y = xy.y;
		}

		const auto [s, c] = FastMath::SinCos(cloudOrientation + 135_deg);
		const auto smat = Mat4x4::Rotate(starRotationAxis, (starTime * Math::Pi));

		return
		{
			.zenithColor			= zenithColor.rgb(),
			.fogHeightSky			= static_cast<float>(fogHeightSky),

			.horizonColor			= horizonColor.rgb(),
			.cloudiness				= static_cast<float>(cloudiness),

			.cloudUVTransform		= Float3{ c, -s, s },
			.cloudScale				= static_cast<float>(cloudScale / 1000.0),

			.cloudTime				= static_cast<float>(cloudTime),
			.cloudPlaneHeight		= static_cast<float>(cloudPlaneHeight),
			.starBrightness			= static_cast<float>(starBrightness * starBrightnessFactor),
			.option					= (uint32(sunEnabled) << 0) | (uint32(cloudsEnabled) << 1) | (uint32(cloudsLightingEnabled) << 2),

			.cloudColor				= cloudColor.rgb(),
			.skyExposure			= static_cast<float>(exposure),

			.starsRoation = {
				SIMD_Float4{ smat.value.r[0] }.toFloat4(),
				SIMD_Float4{ smat.value.r[1] }.toFloat4(),
				SIMD_Float4{ smat.value.r[2] }.toFloat4() },

			.starOffset			= starFrom,
			.starSaturation		= static_cast<float>(starSaturation),
		};
	}
}
