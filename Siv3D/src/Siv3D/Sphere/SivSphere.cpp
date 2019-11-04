//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4305)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4456)
# define PAR_SHAPES_IMPLEMENTATION
# define _CRT_SECURE_NO_WARNINGS
# include <par_shapes/par_shapes.h>
# undef _CRT_SECURE_NO_WARNINGS
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

# include <Siv3D/Sphere.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr size_t VertexCount = 162;
		Array<Float3> g_corners;
		Array<uint16> g_indices;

		void InitSphereMesh()
		{
			par_shapes_mesh* mesh;
			mesh = par_shapes_create_subdivided_sphere(2);

			const size_t vertexCount = mesh->npoints;
			g_corners.resize(vertexCount);
			for (size_t i = 0; i < vertexCount; ++i)
			{
				g_corners[i].set(mesh->points[i * 3], mesh->points[i * 3 + 1], mesh->points[i * 3 + 2]);
			}

			g_indices.assign(mesh->triangles, mesh->triangles + (mesh->ntriangles * 3));

			par_shapes_free_mesh(mesh);
		}
	}

	void Sphere::draw(const Mat4x4& vp, const ColorF& color) const
	{
		static bool initialized = false;

		if (!initialized)
		{
			detail::InitSphereMesh();
			initialized = true;
		}

		const Float2 resolution = Graphics2D::GetRenderTargetSize();
		const Float4 colorF = color.toFloat4();
		const float scale = static_cast<float>(r);
		const Float3 posF = center;

		const size_t vertexCount = detail::g_corners.size();
		std::array<Float3, detail::VertexCount> corners;
		std::memcpy(corners.data(), detail::g_corners.data(), detail::g_corners.size_bytes());

		for (auto& corner : corners)
		{
			corner *= scale;
			corner += posF;
		}

		std::array<Float3, detail::VertexCount> out;
		SIMD::Vector3TransformCoordStream(out.data(), corners.data(), vertexCount, vp);

		for (auto& v : out)
		{
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * resolution.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= resolution.y;
		}

		std::array<Vertex2D, detail::VertexCount> vertices;
		for (size_t i = 0; i < vertexCount; ++i)
		{
			auto& v = vertices[i];
			v.pos = out[i].xy();
			v.color = colorF;
		}

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addSprite(vertices.data(), vertices.size(), detail::g_indices.data(), detail::g_indices.size());
	}

	void Formatter(FormatData& formatData, const Sphere& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.center);
		formatData.string.append(U", "_sv);
		Formatter(formatData, value.r);
		formatData.string.push_back(U')');
	}
}
